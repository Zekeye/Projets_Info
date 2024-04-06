#define _POSIX_C_SOURCE 200809L 
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/termios.h>
#include <time.h>

#define JOUEURS_MAX 4
#define DISTANCE_MAX 50

int Term_non_canonique ()
{
    struct termios term;

    tcgetattr( fileno(stdin), &term );	/* lit les flags du terminal dans term */
    term.c_lflag &= ~ICANON;		/* mode non-canonique */
    term.c_lflag &= ~ECHO;		/* supprime l'écho */
    term.c_cc[VMIN]  = 1;		/* nombre min de caractères */
    term.c_cc[VTIME] = 1;		/* latence (timeout) 1/10e de seconde (0: pas de latence) */
    if (tcsetattr( fileno(stdin), TCSANOW, &term)<0) /* écrit les flags depuis term */
    {
	perror("Term_non_canonique: problème d'initialisation ");
	return 0;
    }
    return 1;
}

/* Term_canonique =====================================
//  Mode normal du clavier: lecture par ligne et écho.
//===================================================*/

int Term_canonique ()
{
    struct termios	term;
			/* retour en mode ligne */
    tcgetattr( fileno(stdin), &term );	/* lit les flags du terminal dans term */
    term.c_lflag |= ICANON;		/* mode canonique */
    term.c_lflag |= ECHO;		/* rétablit l'écho */
    if (tcsetattr( fileno(stdin), TCSANOW, &term)<0) /* écrit les flags depuis term */
    {
	perror("Term_canonique: problème d'initialisation ");
	return 0;
    }
    return 1;
}



void joueur(char my_char, int ligne, int distance){
	struct timespec micro_pause;
	int i;
	char carac;
	int l=JOUEURS_MAX+2;

	printf ("\033[%d;%dH|", ligne+1, 1);
	printf("J%u : Votre caractere est %c\n", ligne, my_char);
	printf ("\033[%d;%dH%c", l+ligne, 1, my_char);
	printf ("\033[%d;%dH|", l+ligne, distance+1);
	fflush (stdout);
	micro_pause.tv_sec = 0; /* secondes */
	micro_pause.tv_nsec = 1000; /* nanosecondes */
	nanosleep( &micro_pause ,NULL);

	while (i<distance){
	  if (read(fileno(stdin), &carac, 1 ) && (carac==my_char)){
	    i++;
	    printf ("\033[H\033[J");
	    printf ("\033[%d;%dH%c", l+ligne, i, carac);
	    fflush (stdout);
	    nanosleep( &micro_pause ,NULL);
	  }
	  nanosleep( &micro_pause ,NULL);
	}
}

int course (int joueurs, int distance){
	int i;	
	char tab_j[JOUEURS_MAX]={'a', 'z', 'e', 'r'};
	char *classement[JOUEURS_MAX]={"\033[31m\033[1mPremier\033[0m", "2e", "3e", "4e"};
	char dernier[] ="\033[94mDernier\033[0m";
	pid_t pid_fils[JOUEURS_MAX], pid_fils_termine,pid_fils_exit;

	fputs("\033[?251", stdout);
	printf("\033[H\033[J");
	fflush(stdout);

	if (!Term_non_canonique()){
		Term_canonique();
		fputs("\033[?25h", stdout);
		exit(1);
	}
	
	for (i=0; i<joueurs; i++){
	  switch(pid_fils[i]=fork()){

	  case -1 :      	   
	  	perror("Echec creation fils");
      	  	exit(2);
    
          case 0 :
	   joueur(tab_j[i], i, distance);
	   exit(i);
	  }
	}

	i=0;
	while ((pid_fils_termine=wait(&pid_fils_exit))>0){
		if (i+1<joueurs){
			printf("%s", classement[i]);
		}
		else{
			printf("%s", dernier);
		}
		printf("\033[K");
		fflush(stdout);
		i++;
	}
	printf("\033[%d;%dH\n", JOUEURS_MAX+joueurs+2,1);
	Term_canonique();
	fputs("\033[?25h", stdout);

	return 0;
			
	
}

int main(int argc, char *argv []){
	int joueurs, distance;


	if(argc>3){
		fprintf(stderr, "Usage: %s joueurs distance \n", argv[0]);
		exit(1);
	}

	if (argc==2){
		joueurs=atoi(argv[1]);
		distance = 10;
	}

	if (argc==3){
		joueurs=atoi(argv[1]);
		distance = atoi(argv[2]);
	}

	else{
		joueurs=2;
		distance = 10;
	}

	if (joueurs < 2 || joueurs > JOUEURS_MAX){
		fprintf(stderr, "Usage: %s joueurs distance \n", argv[0]);
		exit(3);
	}

	if (distance < 2 || distance > DISTANCE_MAX){
		fprintf(stderr, "Usage: %s joueurs distance \n", argv[0]);
		exit(3);
	}
	exit(course(joueurs, distance));
}
