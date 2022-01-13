#ifndef CLIENT_H
#define CLIENT_H


#include "proto.h"

typedef struct client_s
{
    int socket;
}client_t;

int client_init(client_t * client, char *host, char * port);

int client_command(client_t * client, command_type_t type, char * key, char * value, command_t *response);

int client_release(client_t * client);

#endif