#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/select.h>
#include <netinet/in.h>


-------------------------harder query----------------------------
typedef struct head_rq{//
    int Rcode;
    int16_t Id; //Identification
    uint16_t class;//classe
    uint16_t Qdcount;
    uint16_t Nscount;
    uint16_t len_dns;// lenght
    char* d_Data;//data
    char type;// type 
    char ** aliasse;//  aliasses
    struct timeval* d_time; 
    struct addrinfo* addrif;//
} query_cl;
-------------------------------------------------------------------
int main(){
    int sock_client;
    char msg_cli[80], reponse_serv[40];

    struct sockaddr_in addr_client, addr_sev;//definition socket client and server
    addr_sev.sin_family = AF_INET; // type IP
    addr_sev.sin_addr.s_addr = INADDR_ANY;// type adresse(Any tpe)
    
    
    //----------------------------------------------------------------------------------------------------------
    sock_client = socket(AF_INET, SOCK_DGRAM, 0);//create socket
    addr_client.sin_family = AF_INET;// type IP
    addr_client.sin_addr.s_addr = inet_aton("127.0.0.0.1");//address
    addr_client.sin_port = htons(30000);//port
    if(bind(sock_client, (struct sockaddr*)&addr_client, sizeof(addr_client))<0){//if bind wrong
        fprintf(stderr,"Erreur d'attachement");
    }
    bzero(msg_cli, 80);
    strncpy(msg_cli,"C'est un client UDP qui vous join",33);
    sendto(sock_client, msg_cli, sizeof(msg_cli), 0,(struct sockaddr*)&addr_sev, sizeof(addr_sev));//sending
  //  bzero(reponse_serv, 40);
 //  int dc = sizeof(addr_sev);
    //recvfrom(sock_client, reponse_serv, sizeof(reponse_serv),0 ,(struct sockaddr*)&addr_sev, &dc);
    //printf("j'ai reçu du serveur : %s", reponse_serv);
   // close(sock_client);
    
return 0;    
}
