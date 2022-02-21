/**
 * @file serialize.c
 * 
 * @brief Serialization and deserialization.
 */
#include "serialize.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

/**
 * @brief Create a packet to be send with the specified DNS message.
 * 
 * @return The allocated size of the buffer/packet.
 */
static uint8_t *create_buf(dns_msg_t *msg, const size_t align)
{
  uint8_t *pck = NULL; /* The packet to be send. */
  size_t la    = 0;    /* The allocated size of the packet. */

  /* We estimate the length of the header and the question... */
  la = (size_t) (DNS_HEADER_MIN_SIZE + DNS_QUESTION_MIN_SIZE + strlen(msg->name) + 1);

  /* ... and also the length of each resource record. */
  if (msg->rrs)
  {
    /* The exact number of resource records in the packet. */
    int nb_rrs = ntohs(msg->ancount) + ntohs(msg->nscount) + ntohs(msg->arcount);

    dns_rr_t *irr = (dns_rr_t *) msg->rrs;   /* An index to a resource record. */

    do
    {
      la += (size_t) (DNS_RR_MIN_SIZE + strlen(irr->oname) + 1 + irr->length + 1);
      irr++;
    }
    while (--nb_rrs);
  }

  /* We allocate the appropriate amount of memory for the packet to be sent. */

  la++; /* We leave some space for the 'end-transmission' character. */

  pck = mem_aligned_alloc(align, &la);
  memset(pck, 0, la);

  return pck;
}

/**
 * @brief Serialize the header, the query type, and the domain name of a DNS message
 * into a packet.
 * 
 * @return The total amount of serialized data in the buffer/packet.
 */
static long int serialize_hq__(dns_msg_t *msg, uint8_t *pck)
{
  uint8_t *p = (uint8_t *) pck; /* A pointer used to fill the packet to be send. */

  /* Fisrt, we copy each field of header section, which is stored in the packet,
     in the packet. */

  memcpy(p, &(msg->id), sizeof(uint16_t));
  p += sizeof(uint16_t);

  memcpy(p, &(msg->flags), sizeof(uint16_t));
  p += sizeof(uint16_t);

  memcpy(p, &(msg->ancount), sizeof(uint16_t));
  p += sizeof(uint16_t);
  memcpy(p, &(msg->nscount), sizeof(uint16_t));
  p += sizeof(uint16_t);
  memcpy(p, &(msg->arcount), sizeof(uint16_t));
  p += sizeof(uint16_t);

  /* Now, we do the same for the question section. */

  memcpy(p, &(msg->qtype), sizeof(uint16_t));
  p += sizeof(uint16_t);

  /* We leave a '\0' at the end of the string to facilitate deserialization. */
  memcpy(p, msg->name, strlen(msg->name) + 1);
  p += strlen(msg->name) + 1;

  return ( p - pck );
}

/**
 * @brief Serialize a resource record of a DNS message into a packet.
 * 
 * @return The total amount of serialized data in the buffer/packet.
 */
static long int serialize_rr__(dns_rr_t *irr, uint8_t *pck)
{
  uint8_t *p = (uint8_t *) pck; /* A pointer used to fill the packet to be send. */

  /* We copy each field of the current resource record of the packet in the packet. */

  /* To facilitate deserialization, we leave a '\0' at the end of the string. */
  memcpy(p, irr->oname, strlen(irr->oname) + 1);
  p += strlen(irr->oname) + 1;

  memcpy(p, &(irr->type), sizeof(uint16_t));
  p += sizeof(uint16_t);
  memcpy(p, &(irr->ttl), sizeof(int32_t));
  p += sizeof(int32_t);

  memcpy(p, &(irr->length), sizeof(uint16_t));
  p += sizeof(uint16_t);

  /* Same here for the '\0' character. */
  size_t ld = (size_t) (ntohs(irr->length) + 1);
  memcpy(p, irr->data, ld);
  p += ld;

  return ( p - pck );
}

//
uint8_t *serialize(dns_msg_t *msg, const size_t align)
{
  if (!msg)
    return NULL;

  uint8_t *pck = create_buf(msg, align);  /* The packet to be send. */
  long int lsd = 0;                       /* The total amount of serialized data. */

  /* The length of the header and the question is calculated. */
  lsd = (long int) (DNS_HEADER_MIN_SIZE + DNS_QUESTION_MIN_SIZE + strlen(msg->name) + 1);

  /* If a list of resource record exists, we serialize it. */
  if (msg->rrs)
  {
    /* The exact number of resource records to be serialized. */
    int nb_rrs = ntohs(msg->ancount) + ntohs(msg->nscount) + ntohs(msg->arcount);

    dns_rr_t *irr = (dns_rr_t *) msg->rrs;  /* An index to a resource record. */ 
    uint8_t *p    = (uint8_t *) pck;        /* A pointer used to fill the packet. */

    do
    {
      p += lsd;  /* The index in the packet is updated. */

      /* At each step, we serialize a resource record. */
      lsd += serialize_rr__(irr, p);

      irr++;     /* Now, we get the position of the next resource record. */
    }
    while(--nb_rrs);
  }

  /* If the serialized data cannot fit in a single packet... */
  // if (lsd >= UDP_MESSAGES_MAX_SIZE - 2)
  // {
  //   uint16_t flags = ntohs(msg->flags);       /* The header's flags. */

  //   /* ... we indicate in the header that the message is truncated. */
  //   msg->flags = htons((uint16_t) (flags + tc));
  // }

  /* Then, the header, the query type and the domain name must be serialized
     just before the offset. */
  serialize_hq__(msg, pck);

  return pck;
}

/**
 * @brief Deserialize the header, the query type and the domain name of a
 * packet into a DNS message structure.
 * 
 * @return The total amount of deserialized data.
 */
static long int deserialize_hq__(dns_msg_t *msg, uint8_t *pck)
{
  /* First, we save header information. */

  msg->id    = *((uint16_t *) pck);
  msg->flags = *((uint16_t *) (pck + sizeof(uint16_t)));

  msg->ancount = *((uint16_t *) (pck + 2 * sizeof(uint16_t))); 
  msg->nscount = *((uint16_t *) (pck + 3 * sizeof(uint16_t)));
  msg->arcount = *((uint16_t *) (pck + 4 * sizeof(uint16_t)));

  /* Then, we search for the query type and the domain name to be resolved. */

  msg->qtype = *((uint16_t *) (pck + 5 * sizeof(uint16_t)));

  uint8_t *start, *end; /* Index used to find the domain name. */

  /* The fisrt index is set after the query type. */
  start = (uint8_t *) (pck + 6 * sizeof(uint16_t));

  /* The last index must find the end of the string. */
  end = start;
  while (*end != '\0')
    end++;

  /* We copy the the domain name, which is stored between the two indexes. */
  memcpy(msg->name, start, (size_t) (end - start));
  msg->name[end - start] = '\0';

  end++;  /* Calibration: set the pointer after the '\0' character. */

  return ( end - pck );
}

/**
 * @brief Deserialize a resource record of a packet into a DNS message structure.
 * 
 * @return The total amount of deserialized data.
 */
static long int deserialize_rr__(dns_rr_t *irr, uint8_t *pck)
{
  uint8_t *p = (uint8_t *) pck; /* Index used to find domain names. */

  /* First, we search the end of the owner name. */
  while (*p != '\0')
    p++;

  /* Then, we copy the name in the packet. */
  memcpy(irr->oname, pck, (size_t) (p - pck));
  irr->oname[p - pck] = '\0';

  p++;  /* Calibration: set the pointer after the '\0' character. */

  /* We get some numbers... */

  irr->type   = *((uint16_t *) p); 
  irr->ttl    = *((int32_t *) (p + sizeof(uint16_t)));
  irr->length = *((uint16_t *) (p + sizeof(uint16_t) + sizeof(int32_t)));

  /* ... and the transfered data. */

  p += (2 * sizeof(uint16_t) + sizeof(int32_t));

  size_t ld = (size_t) (ntohs(irr->length) + 1);
  memcpy(irr->data, p, ld);
  irr->oname[ntohs(irr->length)] = '\0';
  p += ld;

  return ( p - pck );
}

//
dns_msg_t *deserialize(const uint16_t xid, uint8_t *pck)
{
  if (!pck)
    return NULL;

  long int ldd = 0;  /* The total amount of deserialized data. */

  dns_msg_t *msg = init_dns_msg(xid, 0);

  /* First, we deserialize the header, the query type and the domain name. */
  ldd = deserialize_hq__(msg, pck);

  /* Then, we deserialize the list of resource records. */

  /* The exact number of resource records to be deserialized. */
  int nb_rrs = ntohs(msg->ancount) + ntohs(msg->nscount) + ntohs(msg->arcount);

  if (nb_rrs)
  {
    msg->rrs = malloc((size_t) nb_rrs * sizeof(dns_rr_t));

    dns_rr_t *irr = (dns_rr_t *) msg->rrs;  /* An index to a resource record. */
    uint8_t *p    = (uint8_t *) pck;        /* A pointer used to fill the packet. */

    do
    {
      p += ldd;  /* We update the index. */

      /* At each step, we dserialize a resource record. */
      ldd += deserialize_rr__(irr, p);

      irr++;    /* We get the position of the next resource record. */
    }
    while(--nb_rrs);
  }

  return msg;
}
