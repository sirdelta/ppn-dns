#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/select.h>
#include <netinet/in.h>


//-----------hearder resolve quey----------------
typedef struct head_rq{/
    char addr;//
    char ** aliasse;// 
    struct timeval* d_time; //for used Time To Live
    struct addrinfo* addrif;//
} query_cl;

int main(){
    struct sockaddr_in addr_serv;//  aliase for struct sackaddr
    int sock_srv, sock_client;//definition of the socket
    char msg[40], reponse[80];
    
    sock_srv = socket(AF_INET,SOCK_DGRAM,0);// create socket
    //memset(&addr_serv,0,sizeof(addr_serv));// initiation of buffer
    addr_serv.sin_family = AF_INET;//definition od family IP version
    addr_serv.sin_addr.s_addr = INADDR_ANY;//used all type IP
    addr_serv.sin_port = htons(30000);//definition  port
    bzero(msg,40);//initiationbuffer sending
    strcpy(msg, "C'est un serveur UDP qui te parle");//copy message in buffer
    if(bind(sock_srv,(struct sockaddr*)&addr_serv, sizeof(addr_serv))<0){//if attachement socket do mistake
        fprintf(stderr,"Une erreur s'est produite aucours de l'attachement");
        exit(EXIT_FAILURE);
        
        
        
    }
    else{
        printf("Attachement réussir");
    }
    bzero(reponse,80);//initiation buffer 
    int bd= sizeof(addr_serv);
    recvfrom(sock_client, reponse, sizeof(reponse), 0, (struct sockaddr* )&addr_serv,  &bd);// receve message from client

    printf("Il y a un message de :  : %s\n", reponse);
    //sendto(sock_client, msg, sizeof(msg),0,(struct sockaddr*)&addr_serv, sizeof(addr_serv));// f
    
    close(sock_client);//closing 
    close(sock_srv);// closig
    
        
    
 return 0;   
}
