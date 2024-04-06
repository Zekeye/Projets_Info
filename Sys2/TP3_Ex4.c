#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/termios.h>

int Term_non_canonique ()
{
    struct termios	term;

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



void touche(){
	char carac;
	while (carac!='f'){
	  read(fileno(stdin), &carac, 1 );
	  printf("%d %c\n", getpid(), carac );
	}
}


int main(int argc, char *argv []){
	pid_t pid_fils;
	int i;
	Term_non_canonique ();
	
	for (i=0; i<argc; i++){
	  pid_fils=fork();
	  if (pid_fils==-1){
      	    perror("Echec creation fils");
      	    exit(1);
    	  }
    
          else if (pid_fils){
	    pid_fils=wait(NULL);
	  }

	  else {
	   touche();
	   perror("Touche f frappee");
	   exit(2);
	  }
	}

	Term_canonique ();
	return 0;
}
