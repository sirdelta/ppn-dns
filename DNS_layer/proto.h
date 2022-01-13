#ifndef PROTO_H
#define PROTO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

typedef enum
{
    DNS_SET,
    DNS_GET,
    DNS_DELETE,
    DNS_RESPONSE,
    DNS_COUNT
}command_type_t;

static const char * const command_type_name[DNS_COUNT] = 
{
    "DNS_SET",
    "DNS_GET",
    "DNS_DELETE",
    "DNS_RESPONSE",
};


typedef struct command_s
{
    command_type_t type;
    char key[512];
    char value[512];
}command_t;

#ifdef __cplusplus
}
#endif

#endif /* PROTO_H */