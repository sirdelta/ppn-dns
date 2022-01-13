#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

#include "client.h"
#include "io.h"


int client_init(client_t * client, char *host, char * port)
{
	/* Liste des alternatives
	 * pour se connecter */
	struct addrinfo *res = NULL;
	/* Configuration souhaitée */
	struct addrinfo hints;
	/* Toujours mettre hints a 0 */
	memset( &hints, 0, sizeof( hints ) );
	/* On veut IPV4 ou IPV6, respectivement AF_INET ou AF_INET6 */
	hints.ai_family = AF_UNSPEC;
	/* On veut faire du TCP */
	hints.ai_socktype = SOCK_STREAM;
	/* On lance la résolution DNS
	 * argv[1] : nom de l'hôte
	 * argv[2] : port (exemple 80 pour http)
	 * */
	int ret = getaddrinfo( host, port,
	                       &hints,
	                       &res );

	if ( ret < 0 )
	{
		herror( "getaddrinfo" );
		return 1;
	}

	struct addrinfo *tmp;

	int connected = 0;

	/* On parcours les alternative recues */
	for ( tmp = res; tmp != NULL; tmp = tmp->ai_next )
	{
		/* On crée un socket en suivant la configuration
		 * renvoyéee par getaddrinfo */
		client->socket = socket( tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol );

		if ( client->socket < 0 )
		{
			perror( "sock" );
			continue;
		}

		int ret = connect( client->socket, tmp->ai_addr, tmp->ai_addrlen );

		if ( ret < 0 )
		{
			close( client->socket );
			continue;
		}

		connected = 1;
		break;
	}

	if ( !connected )
	{
		fprintf( stderr, "Failed to connect to %s:%s\n", host, port);
		return 1;
	}

	return 0;
}

int client_command(client_t * client, command_type_t type, char * key, char * value, command_t *response)
{
	/* Send command */
	int ret = send_command(client->socket, type, key, value);
	if(ret != 0)
	{
		return -1;
	}
	/* Read response */
	if( safe_read(client->socket, response, sizeof(command_t)) != 0)
	{
		return -1;
	}

	return 0;
}

int client_release(client_t * client)
{
	close(client->socket);
}

static inline int parse_cli_command(client_t *client, char * cmd)
{
	char * op;
	char * arg1;
	char * arg2;

	op = cmd;

	char * space = strchr(cmd, ' ');

	if(space)
	{
		*space = '\0';
	}
	else
	{
		printf("Cannot find first argument\n");
		return 1;
	}

	arg1 = space + 1;

	int arg1len = strlen(arg1);

	if(!arg1len)
	{
		printf("Cannot find first argument (empty)\n");
		return 1;
	}
	else if(arg1[arg1len - 1] == '\n')
	{
		/* REMOVE the \n */
		arg1[arg1len - 1] = '\0';
	}

	space = strchr(arg1, ' ');

	if(space)
	{
		*space = '\0';

		arg2 = space + 1;

		int arg2len = strlen(arg2);

		if(!arg2len)
		{
			printf("Cannot find second argument (empty)\n");
			return 1;
		}
		else if(arg2[arg2len - 1] == '\n')
		{
			/* REMOVE the \n */
			arg2[arg2len - 1] = '\0';
		}
	}
	else
	{
		arg2 = "";
	}

	command_type_t ctype;

	if(!strcasecmp(op, "GET"))
	{
		ctype = DNS_GET;
	}else if(!strcasecmp(op, "SET"))
	{
		ctype = DNS_SET;
	}else if(!strcasecmp(op, "DEL"))
	{
		ctype = DNS_DELETE;
	}
	else 
	{
		printf("No such command %s (only support GET, SET, DELETE)\n");
		return 1;
	}

	printf("REQ [%s] [%s] [%s]\n", op, arg1, arg2);


	command_t resp;
	client_command(client, ctype, arg1, arg2, &resp);	

	printf("RESP [%s] [%s] [%s]\n", command_type_name[resp.type], resp.key, resp.value);

	return 0;

}


static inline int command_loop(client_t *client)
{
	while(1)
	{
		ssize_t lineSize = 0;
		char *line = NULL;
		size_t len = 0;

		lineSize = getline(&line, &len, stdin);

		if(lineSize < 0)
		{
			break;
		}

		parse_cli_command(client, line);

		free(line);
	}
}

int bench(client_t * client)
{

}



int main( int argc, char **argv )
{
	if(argc != 4 )
	{
		printf("USAGE: \n %s [HOST] [PORT] [MODE]\n\nAvec mode BENCH ou CMD\n", argv[0]);
		return 1;
	}

	client_t client;

	if(client_init(&client, argv[1], argv[2]))
	{
		return 1;
	}

	if(!strcmp(argv[3], "CMD"))
	{
		printf("Tapez une commande :\n\t - GET [KEY]\n\t - SET [KEY] [VALUE]\n\t - DEL [KEY]\n");
		command_loop(&client);
	}
	else if(!strcmp(argv[3], "BENCH"))
	{
		bench(&client);
	}
	else
	{
		printf("No such command expecting either BENCH or CMD");
	}



	client_release(&client);

	return 0;
}