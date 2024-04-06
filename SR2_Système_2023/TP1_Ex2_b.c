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
	
	printf("Processus de pid %d : protege contre SIGINT\n", getpid());
	printf("Processus de pid %d : Je vais devenir l'executable boucler pour afficher 10 fois toutes les 2 secondes\n", getpid());
		
	printf("%d\n",execl("/SR2_Système_2023/TP1_Ex2.c", "10", "2", NULL));	
	
	
	return 0;
}
