#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <time.h>

int nb=0, tube[2], signalRecu=0, delai=0;
char c[30]="Message envoye";
time_t t;

void timeout (int sigRecu) {
	signalRecu = 1;
	write(tube[1], (void *)&c, sizeof(char));
}

void fils(){
//orientation des tubes
	close(tube[1]);
	for(int i=1; i<=nb; i++){
		read(tube[0],(void*)c, sizeof(char));
		printf("	Fils - reçu de mon pere : %s %d envoye a %s \n", &c, i, (time(&t),ctime(&t)));
	}
	close(tube[0]);
	printf("	Fils - je me termine a %s\n", (time(&t),ctime(&t)));
}

void pere(){
//orientation des tubes
	close(tube[0]);
	sigset_t masqueOriginal, masqueAttente;
	struct sigaction action;
	action.sa_handler = timeout;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;

	if (sigaction(SIGALRM, &action, NULL) < 0){
		perror("Echec sigaction");
		exit(2);
	}

	for(int i=1; i<=nb; i++){
		sigemptyset(&masqueAttente);
		sigaddset(&masqueAttente, SIGALRM);
		sigprocmask(SIG_BLOCK, &masqueAttente, &masqueOriginal);
		for(int j=0; j<delai; j++){
			while(signalRecu)
				signalRecu=0;
				sigsuspend(&masqueOriginal);
		}
	}
	close(tube[1]);
	sigprocmask(SIG_UNBLOCK, &masqueAttente, NULL);
	printf("	Pere - je me termine en dernier a %s\n", (time(&t),ctime(&t)));
}


int main(int argc, char** argv){
	int tube[2];
	nb=atoi(argv[2]);
	delai=atoi(argv[1]);

	if(argc!=3){
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

		default :
			pere();
			exit(0);
	}
	return 0;
}
