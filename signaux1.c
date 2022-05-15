#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
int main(void) {
 sigset_t ens1,ens2;
 int sig;
 /* Construction ensemble {SIGINT,SIGQUIT,SIGUSR1}  */ 
 /* sigemptyset initialise l'ens. de signaux à vide */
 sigemptyset(&ens1);
 sigaddset(&ens1,SIGINT);
 sigaddset(&ens1,SIGQUIT);
 sigaddset(&ens1,SIGUSR1);
 /* Mise en place du masquage des signaux de cet ens. */
 sigprocmask(SIG_SETMASK,&ens1,(sigset_t *)0);
 printf("Masquage mis en place.\n");
 sleep(10);/*le temps de latence on peut le varié selon nos besoin */
 /*Lecture des signaux envoyés mais non délivrés car masqués*/
 sigpending(&ens2);
 printf("Signaux pendants:\n");      
 for(sig=1;sig<NSIG;sig++) if(sigismember(&ens2,sig)) printf("%d \n",sig);      
 sleep(5);      
 /* Suppression du masquage des signaux */      
 sigemptyset(&ens1);      
 printf("Déblocage des signaux.\n");      
 sigprocmask(SIG_SETMASK,&ens1,(sigset_t *)0);      
 sleep(15);      
 printf("Fin normale du processus\n");      
 exit(0);      
}
