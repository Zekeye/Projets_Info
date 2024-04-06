#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>

pid_t pid;

void traiterSignal(int sig){
	printf("Ctrl-C/SIGINT  reçu  par  le  processus de n°%d\n", getpid());
}

void fils () {
	while(1){
	printf("\nFils :Je suis le processus %d\n", getpid());
	sleep(2);
	}
}

int main(int argc, char** argv){
	struct sigaction affichage;
	affichage.sa_handler=traiterSignal;
	sigemptyset(&(affichage.sa_mask));
	affichage.sa_flags = 0;
	sigaction(SIGINT, &affichage, NULL);
	printf("Père : Je suis le processus %d\n", getpid());

	switch(pid=fork()){
		case -1:
			perror("Echec");
			exit(1);
		case 0 :
			fils();
	}
	while(wait(NULL)==-1){
		sleep(2);
	}
	return 0;
}
