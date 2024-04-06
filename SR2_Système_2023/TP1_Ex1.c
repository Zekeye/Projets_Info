#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>



void traiterSignal(int sig){
	printf("Ctrl-C/SIGINT  reçu  par  le  processus  de  n°%d\n", getpid());
}

int main(int argc, char** argv){
	int pid = getpid();
	struct sigaction affichage;
	affichage.sa_handler=traiterSignal;

	while(1){
		printf("Je suis le processus %d\n", pid);
		sleep(2);
		sigaction(SIGINT, &affichage, NULL);			
	}
	return 0;
}
