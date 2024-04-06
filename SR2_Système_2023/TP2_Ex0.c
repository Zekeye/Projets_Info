#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>

int nb, tube[2];
char c[30]="Message envoye";

void fils(){
//orientation des tubes
	close(tube[1]);
	for(int i=1; i<=nb; i++){
		read(tube[0],(void*)c, sizeof(char));
		printf("	Fils - reçu de mon pere : %s %d  \n", &c, i);
		sleep(2);
	}
	close(tube[0]);
	printf("	Fils - je me termine\n");
}

void pere(){
//orientation des tubes
	close(tube[0]);
	for(int i=1; i<=nb; i++){
		printf("Pere - %s %d envoye\n", &c, i);
		write(tube[1], (void *)&c, sizeof(char));
		sleep(2);
	}
	close(tube[1]);
	printf("Pere - je me termine en dernier\n");
}


int main(int argc, char** argv){
	int tube[2];
	nb=atoi(argv[1]);

	if(argc!=2){
		printf("Err arg\n");
		exit(1);
	}

	if(pipe(tube)==-1){
		perror("Err tube\n");
		exit(2);
	}

	switch(fork()){
		case -1 :
			printf("Err fils\n");
			exit(3);

		case 0 :
			fils();
			exit(0);

		default : pere();
		exit(0);
	}
	return 0;
}
