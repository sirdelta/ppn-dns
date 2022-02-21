/**
 * @file dns_proto.h
 * 
 * @brief The strutures and elements of the DNS protocol.
 * 
 * @see https://datatracker.ietf.org/doc/html/rfc1034
 * @see https://datatracker.ietf.org/doc/html/rfc1035
 */
#ifndef DNS_PROTO__H
#define DNS_PROTO__H

#include "parameters.h"
#include "rand.h"
#include <stdio.h>
#include <stdint.h>

/**
 * @brief Header's flags of a DNS request.
 */
enum dns_header_flags_e
{
  /* QR values */
  // qr_mask   = 0x8000,
  qr_query  = 0x0000,
  qr_reply  = 0x8000,

  /* OPCODE values */
  // opcode_mask           = 0x7800,
  opcode_standard_query = 0x0000,
  opcode_inverse_query  = 0x0800,
  opcode_status         = 0x1000,

  aa = 0x0400,  /* authoritative answer bit */
  tc = 0x0200,  /* truncation bit */
  rd = 0x0100,  /* recursion desired bit */
  ra = 0x0080,  /* recursion available bit */

  // xx = 0x0040,  /*  */
  cp = 0x0020,  /* compressed message */
  en = 0x0010,  /* end of transmission */

  /* RCODE values */
  // rcode_mask            = 0x000f,
  rcode_no_error        = 0x0000,
  rcode_format_error    = 0x0001,
  rcode_server_failure  = 0x0002,
  rcode_name_error      = 0x0003,
  rcode_not_implemented = 0x0004,
  rcode_refused         = 0x0005
}
dns_header_flags;

/**
 * @brief Command type values of a DNS request.
 */
enum dns_ctype_values_e
{
  GET      = 1,
  PUT      = 2,
  UPDATE   = 3,
  DELETE   = 4,
  RESPONSE = 5
}
dns_ctype_values;

/**
 * @brief Query type values of a DNS request.
 */
enum dns_qtype_values_e
{
  A     = 1,    /* an IPV4 host address */
  NS    = 2,    /* an authoritative name server */
  CNAME = 5,    /* the canonical name for an alias */
  SOA   = 6,    /* the start of a zone of authority */
  PTR   = 12,   /* a domain name pointer */
  HINFO = 13,   /* host system information */
  TXT   = 16,   /* text string */
  AAAA  = 28,   /* an IPV6 host address */
  ANY   = 255   /* any information */
}
dns_qtype_values;

/**
 * @brief Command type names of a DNS request.
 */
static const char *dns_ctype_names[6] = {"GET", "PUT", "UPDATE", "DELETE", "RESPONSE", NULL};

/**
 * @brief Query type names of a DNS request.
 */
static const char *dns_qtype_names[10] = {"A", "NS", "CNAME", "SOA", "PTR", "HINFO", "TXT", "AAAA", "ANY", NULL};

/**
 * @brief The resource record structure of a DNS request.
 */
typedef struct dns_rr_s
{
  char oname[NAMES_SIZE_LIMIT + 1];  /* the name of the owner node */
  uint16_t type;    /* the query type */
  int32_t ttl;      /* the time interval before caching it */
  uint16_t length;  /* the length of the transfered data */
  char data[DNS_DATA_BUFFER_LENGTH + 1];  /* the transfered data */
}
dns_rr_t;

/**
 * @brief The DNS request structure.
 */
typedef struct dns_msg_s
{
  uint16_t id;      /* header's identification number */
  uint16_t flags;   /* header's flags */
  uint16_t ancount; /* number of answer record(s) */
  uint16_t nscount; /* number of name server record(s) */
  uint16_t arcount; /* number of additional record(s) */

  uint16_t ctype;   /* the command type */
  uint16_t qtype;   /* the query type */
  char name[NAMES_SIZE_LIMIT + 1];  /* the domain name to be resolved */

  dns_rr_t *rrs;    /* list of resource records */
}
dns_msg_t;

/**
 * @brief Create and initialize a DNS request.
 */
dns_msg_t *init_dns_msg(const uint16_t xid, const size_t nb_rrs);

/**
 * @brief Destroy the specified DNS request structure. 
 */
void release_dns_msg(dns_msg_t *msg);

/**
 * @brief Parse the format of a command type to be stored.
 * 
 * @return If it is a valid command type, a positive integer is returned.
 * If it is not, 0 is returned.
 */
uint16_t get_ctype_value(const char *cname);

/**
 * @brief Parse the format of a query type to be stored.
 * 
 * @return If it is a valid query type, a positive integer is returned.
 * If it is not, 0 is returned.
 */
uint16_t get_qtype_value(const char *qname);

/**
 * @brief Display the content of the specified DNS request.
 * Before being printed, numbers are converted to host byte order.
 * 
 * @see byteorder(3)
 */
void print_dns_msg(dns_msg_t *msg);

#endif  //DNS_PROTO__H
