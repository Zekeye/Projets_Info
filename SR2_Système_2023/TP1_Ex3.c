#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <time.h>

pid_t pidFils;


void fils (int i) {
	printf("\nCapteur (%d) (%d) : %d vehicules en plus => %d\n", getpid());
	sleep(2);
	}
}

int main(int argc, char** argv){
	struct sigaction affichage;
	affichage.sa_handler=traiterSignal;
	sigemptyset(&(affichage.sa_mask));
	affichage.sa_flags = 0;
	sigaction(SIGINT, &affichage, NULL);
	printf("Père (%d) - Capteur %d : nombre de vehicules = %d\n", getpid());

	for(i=0; i<2; i++){
	switch(pidFils[]=fork()){
		case -1:
			perror("Echec");
			exit(1);
		case 0 :
			fils(i);
			break;
	}
	int cr;
	pid_t filsTerminé;
	while((filsTerminé=wait(&cr)=!=-1){
		printf("%lu est termoné %d\n", filsTerminé, WEXITSTATUS(cr));
	}
	return 0;
}
