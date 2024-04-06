#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char *argv[]){
	int pid = getpid();
	time_t t;
	if (argc != 3) {
		printf("Usage : %s\n", argv[0]);
		exit(1);
	}
	int nbf=atoi(argv[1]);
	int nbs=atoi(argv[2]);
	
	for(int i=0; i<=nbf; i++){
		
		printf("Je suis le processus %d, il est %s\n", pid, (time(&t), ctime(&t)));
		sleep(nbs);
	}
	
	return 0;
}
