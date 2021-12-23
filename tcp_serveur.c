#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/select.h>
#include <netinet/in.h>


//--------------------Proposition of header of resolution of the query---------------------
typedef struct head_rq{//struct whit different attribute 
    char addr;//addresse of each job
    char ** aliasse;// the aliases
    struct timeval* d_time; //struct that we use of Time To Live
    struct addrinfo* addrif;//struct that we use to get the name or resolve the name or addres (else) 
} query_cl;


int main(){
    int sock_cli;
    int sock_server = socket(PF_INET, SOCK_STREAM, 0);//creation of the socket
    char Msg_cli[80];
    struct sockaddr_in addr_server;//structure of server address
    addr_server.sin_family = AF_INET;/definition of the family daddress ip here IPv4
    addr_server.sin_port = htons(30000);//whit a port 30000

    if(bind(sock_server,(struct sockaddr*)&addr_server, sizeof(addr_server))<0){//attachement of socket
        fprintf(stderr,"L'attachement à une connetion a échouée");
        exit(EXIT_FAILURE);// exit if bind do mistake
    }
    else
        printf("Attachement réussir\n");
    
    listen(sock_server, 5);//waiting five connexion
    
    int msg = accept(sock_server, (struct sockaddr*)&addr_server, &sock_server);// Fonction of acceptation of connexion
    
    bzero(Msg_cli,80);//initiation of buffer 
    
    read(msg, Msg_cli, sizeof(Msg_cli));//reception of message et reading
    printf("Voici le mesage du client  : %s", Msg_cli);
    
    write(msg, "salut les gars",14);//sending or writin
    close(msg);//closing buffer
    close(sock_server); //closing socket
    
    return 0;
    
}
