/**
 * @file dns_proto.c
 * 
 * @brief The strutures and elements of the DNS protocol.
 */
#include "dns_proto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

//
dns_msg_t *init_dns_msg(const uint16_t xid, const size_t nb_rrs)
{
  dns_msg_t *msg = malloc(sizeof(dns_msg_t));

  /* A new unique id is generated and header's values are set. */
  msg->id      = htons((uint16_t) li_rand(xid));
  msg->flags   = htons(0);
  msg->ancount = htons(0);
  msg->nscount = htons(0);
  msg->arcount = htons(0);

  /* The question section is set. */
  msg->ctype = htons(0);
  msg->qtype = htons(0);
  memset(msg->name, 0, NAMES_SIZE_LIMIT);

  /* The list of resource records is desallocated... */
  if (msg->rrs)
    free(msg->rrs);
  msg->rrs = NULL;

  /* ... but if necessary, we reallocate a new one. */
  if (nb_rrs)
  {
    msg->rrs = malloc(nb_rrs * sizeof(dns_rr_t));
    
    dns_rr_t *irr = (dns_rr_t *) msg->rrs;  /* An index to a resource record. */
    size_t count  = 0;                      /* Count the number of records. */

    do
    {
      memset(irr->oname, 0, NAMES_SIZE_LIMIT);
      irr->type   = htons(0);
      irr->ttl    = (int32_t) htonl(0);
      irr->length = htons(0);
      memset(irr->data, 0, DNS_DATA_BUFFER_LENGTH);

      count++;  /* Increment the total number of initialized records. */
      irr++;    /* Get the position of the next one. */
    }
    while(count < nb_rrs);
  }

  return msg;
}

//
void release_dns_msg(dns_msg_t *msg)
{
  if (!msg)
    return;

  if (msg->rrs)
    free(msg->rrs);

  free(msg);
}

//
uint16_t get_ctype_value(const char *cname)
{
  if (!cname)
    return 0;

  size_t lc = strlen(cname);  /* The length of the input command name. */

  /* The name must match with only one authorized command type. */
  switch (lc)
  {
    case 3:
      if (strncmp("GET", cname, 3) == 0)
        return GET;
      if (strncmp("PUT", cname, 3) == 0)
        return PUT;
      break;

    case 6:
      if (strncmp("UPDATE", cname, 6) == 0)
        return UPDATE;
      if (strncmp("DELETE", cname, 6) == 0)
        return DELETE;
      break;

    case 8:
      if (strncmp("RESPONSE", cname, 8) == 0)
        return RESPONSE;
      break;

    default:
      return 0;
  }

  return 0;
}

//
uint16_t get_qtype_value(const char *qname)
{
  if (!qname)
    return 0;

  size_t lq = strlen(qname);  /* The length of the input query name. */

  /* The name must match with only one authorized query type. */
  switch (lq)
  {
    case 1:
      if (strncmp("A", qname, 1) == 0)
        return A;
      break;

    case 2:
      if (strncmp("NS", qname, 2) == 0)
        return NS;
      break;

    case 3:
      if (strncmp("SOA", qname, 3) == 0)
        return SOA;
      if (strncmp("PTR", qname, 3) == 0)
        return PTR;
      if (strncmp("TXT", qname, 3) == 0)
        return TXT;
      if (strncmp("ANY", qname, 3) == 0)
        return ANY;
      break;

    case 4:
      if (strncmp("AAAA", qname, 4) == 0)
        return AAAA;
      break;

    case 5:
      if (strncmp("CNAME", qname, 5) == 0)
        return CNAME;
      if (strncmp("HINFO", qname, 5) == 0)
        return HINFO;
      break;

    default:
      return 0;
  }

  return 0;
}

/**
 * @brief Return the name of the input command type.
 */
static size_t get_ctype_index__(const uint16_t cval)
{
  size_t pos = 4;

  switch (ntohs(cval))
  {
    case GET:     pos = 0; break;
    case PUT:     pos = 1; break;
    case UPDATE:  pos = 2; break;
    case DELETE:  pos = 3; break;
    case RESPONSE:
    default:      pos = 4;
  }

  return pos;
}

/**
 * @brief Return the name of the input query type.
 */
static size_t get_qtype_index__(const uint16_t qval)
{
  size_t pos = 8;

  switch (ntohs(qval))
  {
    case A:     pos = 0; break;
    case NS:    pos = 1; break;
    case CNAME: pos = 2; break;
    case SOA:   pos = 3; break;
    case PTR:   pos = 4; break;
    case HINFO: pos = 5; break;
    case TXT:   pos = 6; break;
    case AAAA:  pos = 7; break;
    case ANY:
    default:    pos = 8;
  }

  return pos;
}

//
void print_dns_msg(dns_msg_t *msg)
{
  if (!msg)
    return;

  //
  uint16_t flags = ntohs(msg->flags); /* Used to store the header's flags. */
  char *opcode   = NULL;              /* Used to store the OPCODE value. */
  char *rcode    = NULL;              /* Used to Store the RCODE value. */

  if (flags & opcode_inverse_query)
    opcode = "inverse";
  else if (flags & opcode_status)
    opcode = "status";
  else
    opcode = "standard";

  if (flags & rcode_format_error)
    rcode = "format error";
  else if (flags & rcode_server_failure)
    rcode = "server failure";
  else if (flags & rcode_name_error)
    rcode = "name error";
  else if (flags & rcode_not_implemented)
    rcode = "not implemented";
  else if (flags & rcode_refused)
    rcode = "refused";
  else
    rcode = "no error";

  printf("> ID:%d [%s %s] - %s -%s%s%s%s\n  answer: %d, authority: %d, additional: %d\n",
    ntohs(msg->id),
    (flags & qr_reply) ? "reply" : "query",
    opcode,
    rcode,
    (flags & aa) ? " aa" : "",
    (flags & tc) ? " tc" : "",
    (flags & rd) ? " rd" : "",
    (flags & ra) ? " ra" : "",
    ntohs(msg->ancount),
    ntohs(msg->nscount),
    ntohs(msg->arcount));

  //
  printf("> [?] %s\n  %s %17s %5s\n",
    dns_ctype_names[get_ctype_index__(msg->ctype)],
    msg->name,
    "IN",
    dns_qtype_names[get_qtype_index__(msg->qtype)]);

  //
  uint16_t ancount = ntohs(msg->ancount); /* Number of answer record(s). */
  uint16_t nscount = ntohs(msg->nscount); /* Number of name server record(s). */
  uint16_t arcount = ntohs(msg->arcount); /* Number of additional record(s). */

  if (!ancount && !nscount && !arcount)
    return;

  dns_rr_t *irr  = (dns_rr_t *) msg->rrs; /* Used to index a resource record. */
  uint16_t count = 0;                     /* Used to count the number of records. */

  /* Print answer resource record. */
  if (ancount)
  {
    printf("> [answer]\n");

    for (count = 0; count < ancount; count++)
    {
      /* Print the current answer. */
      printf("  %s %13d %3s %5s    %s\n",
        irr->oname,
        ntohl((uint32_t) irr->ttl),
        "IN",
        dns_qtype_names[get_qtype_index__(irr->type)],
        irr->data);
      
      irr++; /* Get the position of the next one. */
    }
  }

  /* Print authority resource record. */
  if (nscount)
  {
    printf("> [authority]\n");

    for (count = 0; count < nscount; count++)
    {
      /* Print the current authority information. */
      printf("  %s %13d %3s %5s    %s\n",
        irr->oname,
        ntohl((uint32_t) irr->ttl),
        "IN",
        dns_qtype_names[get_qtype_index__(irr->type)],
        irr->data);
      
      irr++; /* Get the position of the next one. */
    }
  }

  /* Print additionnal resource record. */
  if (arcount)
  {
    printf("> [additional]\n");

    for (count = 0; count < arcount; count++)
    {
      /* Print the current additional information. */
      printf("  %s %13d %3s %5s    %s\n",
        irr->oname,
        ntohl((uint32_t) irr->ttl),
        "IN",
        dns_qtype_names[get_qtype_index__(irr->type)],
        irr->data);
      
      irr++; /* Get the position of the next one. */
    }
  }
}
