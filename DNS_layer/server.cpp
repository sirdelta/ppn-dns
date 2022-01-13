#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>  /* -lpthread */
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

#include "proto.h"
#include "io.h"


#include <map>
#include <string>

using namespace std;

map <string,string> request_cache;

static inline string resolve_addr(char *host)
{
	string sret = "";

	struct addrinfo *res = NULL;
	struct addrinfo hints;
	memset( &hints, 0, sizeof( hints ) );
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	int ret = getaddrinfo( host, "80",
	                       &hints,
	                       &res );

	if ( ret < 0 )
	{
		if(errno == EAI_SYSTEM)
		{
			perror("getaddrinfo");
		}
		else
		{
			herror( "getaddrinfo" );
		}
		return "";
	}

	struct addrinfo *tmp;

	for ( tmp = res; tmp != NULL; tmp = tmp->ai_next )
	{
		char ip[INET6_ADDRSTRLEN];
		ip[0] = '\0';

		char buff[128];

		if ( tmp->ai_family == AF_INET )
		{
			struct sockaddr_in *saddr = ( struct sockaddr_in * )tmp->ai_addr;
			inet_ntop( AF_INET, &saddr->sin_addr, ip, sizeof( ip ) );
			snprintf( buff, 128, " IPV4 : %s ", ip );
			sret += buff;
		}
		else if ( tmp->ai_family == AF_INET6 )
		{
			struct sockaddr_in6 *saddr6 = ( struct sockaddr_in6 * )tmp->ai_addr;
			inet_ntop( AF_INET6, &saddr6->sin6_addr, ip, sizeof( ip ) );
			snprintf( buff, 128, " IPV6 : %s ", ip  );
			sret += buff;
		}
	}

	return sret;
}




static inline int process_command(int fd, command_t *cmd)
{
	printf("PROCESSING [%s] [%s] [%s]\n", command_type_name[cmd->type], cmd->key, cmd->value);
	command_t resp;
	resp.type = DNS_RESPONSE;

	snprintf(resp.key, 512, cmd->key);

	switch(cmd->type)
	{
		case DNS_SET:
			request_cache[cmd->key] = cmd->value;
		break;
    	case DNS_GET:
		{
			map<string,string>::iterator it = request_cache.find(cmd->key);
			string val;
			if(it != request_cache.end())
			{
				printf("FROM CACHE\n");
				val = it->second;
				snprintf(resp.value, 512, val.c_str());
			}
			else
			{
				/* If not present try DNS */
				string resolution_dns = resolve_addr(cmd->key);

				if(resolution_dns.length() != 0)
				{
					printf("FROM DNS RESOLUTION\n");
					/* We managed to do some DNS */
					/* Add to cache */
					request_cache[cmd->key] = resolution_dns;
					snprintf(resp.value, 512, resolution_dns.c_str());
				}
				else
				{
					snprintf(resp.key, 512, "NOK");
					snprintf(resp.value, 512, "NOK");
				}
			}
		}
		break;
    	case DNS_DELETE:
			if( request_cache.erase(cmd->key) )
			{
				snprintf(resp.value, 512, "OK");
			}
			else
			{
				snprintf(resp.value, 512, "NOK");
			}
		break;
	}


	return safe_write(fd, &resp, sizeof(command_t));
}


struct client_infos
{
	int client_socket;
};


void *client_loop( void *param )
{
	struct client_infos *info = ( struct client_infos * )param;

	char buff[128];
	int ret = 0;

	command_t cmd;

	while( safe_read(info->client_socket, &cmd, sizeof(command_t)) != -1)
	{
		if( process_command(info->client_socket, &cmd) != 0 )
		{
			break;
		}
	}
 
	fprintf( stderr, "Closing client socket\n" );
	/* On se déconnecte du client */
	close( info->client_socket );

	return NULL;
}


int main( int argc, char **argv )
{
	/* Valeur de retour de getaddrinfo
	 * avec les alternatives pour configurer
	 * le serveur en fonction des hints */
	struct addrinfo *res = NULL;
	/* Ces paramètres définissent comment
	 * le serveur doit être configuré */
	struct addrinfo hints;
	/* Toujours mettre la structure a 0 */
	memset( &hints, 0, sizeof( hints ) );
	/* Peu importe le protocole IPV4 (AF_INET)
	 * ou IPV6 (AF_INET6) */
	hints.ai_family = AF_UNSPEC;
	/* Nous voulons un socket TCP */
	hints.ai_socktype = SOCK_STREAM;
	/* Ce paramètre permet d'écouter
	 * hors de la machine locale */
	hints.ai_flags = AI_PASSIVE;

	/* Ce programme attend un paramètre qui est le port */
	if ( argc != 2 )
	{
		return 1;
	}

	signal(SIGPIPE, SIG_IGN);

	/* Ici getaddrinfo permet de générer les
	 * configurations demandées */
	int ret = getaddrinfo( NULL, argv[1],
	                       &hints,
	                       &res );

	if ( ret < 0 )
	{
		herror( "getaddrinfo" );
		return 1;
	}

	struct addrinfo *tmp;

	int listen_sock = -1;

	int binded = 0;

	/* Nous allons parcourir les différentes
	 * configurations pour trouver une qui marche
	 * ces configurations sont définies par les hints */
	for ( tmp = res; tmp != NULL; tmp = tmp->ai_next )
	{
		/* On crée un socket */
		listen_sock = socket( tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol );

		if ( listen_sock < 0 )
		{
			perror( "sock" );
			continue;
		}

		/* On attache ce socket à un port donné (argument passé à getaddr) */
		ret = bind( listen_sock, tmp->ai_addr, tmp->ai_addrlen );

		if ( ret < 0 )
		{
			close( listen_sock );
			perror( "bind" );
			continue;
		}

		binded = 1;
		break;
	}

	if ( !binded )
	{
		fprintf( stderr, "Failed to bind on 0.0.0.0:%s\n", argv[1] );
		return 1;
	}

	/* On commence a ecouter */
	ret = listen( listen_sock, 2 );

	if ( ret < 0 )
	{
		perror( "listen" );
		return 1;
	}

	/* On va maintenant accepter une connexion */
	/* Ceci sera remplis par
	 * accept et décrit le client (ip port)*/
	struct sockaddr client_info;
	socklen_t addr_len;
	fprintf( stderr, "Before accept\n" );

	while ( 1 )
	{
		/* On accepte un client et on récupére un nouveau FD */
		int client_socket = accept( listen_sock, &client_info, &addr_len );
		fprintf( stderr, "After accept\n" );

		if ( client_socket < 0 )
		{
			perror( "accept" );
			return 1;
		}

		struct client_infos *infos = ( struct client_infos * )malloc( sizeof( struct client_infos ) );

		infos->client_socket = client_socket;

		pthread_t th;

		pthread_create( &th, NULL, client_loop, ( void * ) infos );
	}

	/* On ferme le serveur */
	close( listen_sock );
	return 0;
}