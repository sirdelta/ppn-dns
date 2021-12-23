#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/select.h>
#include <netinet/in.h>
//------------------hearder query------------------------
typedef struct set_req{
    char* name;
    char* ip_dns;
    char* aliase;
    
}set_req;
/*
typedef struct head_rq{//structure comprtant les différent attributs possibles
    //int Rcode;
    int16_t Id; //l'identifiant
    uint16_t len_dns;// la taille de la donnée 
    char* d_Data;// la donnée
    char type;//son type 
    char ** aliasse;// ces aliasses
   // struct timeval d_time; //la stucture à manipuler pour utiliser le Time To Live
   // struct addrinfo addrif;//La structure à manipuler pour avoir le nom, le canonical name et autre 
} query_cl;

*/


int main(){
    char space[80],don[30];
    char c;
    //char*tab = (tab*)(malloc(sizeof(char)));
    char *tab = {"12.234.3675.3"};
   // memset(tab,0,sizeof(tab));
    int menu = 3;
    struct sockaddr_in addr_cli;//aliase of struct sockaddr
    int serv_addr;
    int socket_clien = socket(PF_INET, SOCK_STREAM, 0); //create socket 
    memset(&addr_cli, 0, sizeof(addr_cli));//create and initiation of space
    addr_cli.sin_family = AF_INET; //define type of IP version 
    addr_cli.sin_addr.s_addr = inet_addr("127.0.0.7");//addre IP 
    addr_cli.sin_port = htons(30000);//port tha we ue     

    if(connect(socket_clien, (const struct sockaddr*)&addr_cli, sizeof(addr_cli))< 0){// if error of connexion
        fprintf(stderr, "Erreur de connect\n");
	    exit(EXIT_FAILURE);
    
}
    bzero(space,80);// initiation buffer
    strcpy(space, "C'est un debut chaud client");// copy of message

    send(socket_clien, space,sizeof(space),0);// send to server

    bzero(don,30);//initiation buffer sending
    read(socket_clien, don,sizeof(don));// reception of message or reading of message
    fprintf(stderr, "ici est parvenue du serveur ça : %s.\n", don);

    close(socket_clien); //close socket

    


return 0;

}






