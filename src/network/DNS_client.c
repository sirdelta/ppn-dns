#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>


//--------------------------header of query on DNS--------------------------------
    int16_t Id;
    //char Qr;
   // int Opcode;
   // char Aa;
  //  char Tc;
  //  char Rd;
  //  char Ra;
    //char Z;
    //char AA;
   // char NAD;
    int Rcode;
    uint16_t Qdcount;
    uint16_t Nscount;
} head_d;

typedef struct RR_dns {
    char* d_Nom;
    char d_Type;
    uint16_t d_Class;
    uint16_t d_TTL;
    uint16_t len_dns;
    char* d_Data;

}R_dns;

typedef struct addrinfo{
    int ai_flags;
    int ai_amily;
    int ai_socktype;
    int ai_protocol;
    socklen_t ai_addrlen;
    struct sockaddr * ai_addr;
    char * ai_cannoname;
    struct addrinfo *ai_next;
}adinf;







//------------------------------creation of connection ------------------------------
int socket_dns = socket(AF_INET, SOCK_DGRAM,0);
menset(&addr, 0, sizeof(addr));
struct sockaddr_in addr;
addr.sin_family = AF_UNSPEC;
addr.sin_addr.s_addr = htonl(INADDR_ANY);
addr.sin_port = htons(53);
if(connect(addr, (const struct sockaddr* addr, sizeof(addr))< 0){
    fprintf(stderr, "Erreur de connect\n");
    
}
else{
    printf("Connection réussir");
}
    









