#define _POSIX_C_SOURCE 200809L  /* Respecte la norme POSIX 200809 : IEEE Std 1003.1-2008 */
#include <stdio.h>              
#include <stdlib.h>            
#include <sys/types.h>         
#include <unistd.h>             
#include <sys/wait.h>           
#include <sys/termios.h>  /* le terminal non canonique */     
#include <time.h>  /* Pour nanosleep */           

#define NB_MAX_JOUEURS  4 
#define DISTANCE_MAX    40 


/* Term_non_canonique =================================
//  Permet de lire le clavier touche par touche, sans
// écho.
//===================================================*/

int Term_non_canonique ()

{
	struct termios      term;

	tcgetattr( fileno(stdin), &term );  /
	term.c_lflag &= ~ICANON;            /* mode non-canonique */
	term.c_lflag &= ~ECHO;              /* supprime l’echo */
	term.c_cc[VMIN]  = 1;               /* nombre min de caractères */
	term.c_cc[VTIME] = 1;               /* latence (timeout) 1/10e de seconde (0: pas de latence) */
	if (tcsetattr( fileno(stdin), TCSANOW, &term)<0) /* ecrit les flags depuis term */
	{
		perror("Term_non_canonique: problème d’initialisation ");
		return 0;
	}
	return 1;
}

/* Term_canonique =====================================
//  Mode normal du clavier: lecture par ligne et echo.
//===================================================*/

int Term_canonique ()
{
	struct termios      term;
					/* retour en mode ligne */
	tcgetattr( fileno(stdin), &term );  /* lit les flags du terminal dans term */
	term.c_lflag |= ICANON;             /* mode canonique */
	term.c_lflag |= ECHO;               /* retablit l’echo */
	if (tcsetattr( fileno(stdin), TCSANOW, &term)<0) /* ecrit les flags depuis term */
	{
		perror("Term_canonique: problème d’initialisation ");
		return 0;
	}
	return 1;
}

void mon_exit(int exit_value)
{
	Term_canonique();
	fputs("\033[?25h", stdout);
	exit(exit_value);
}

void joueur(char my_char, int ligne, int distance)
{
	int c;
	int cpt=0;
	int row=NB_MAX_JOUEURS+2;
	struct timespec micro_pause;
	printf ("\033[%d;%dH", ligne+1, 1);   
	printf("joueur %u : tapez %c", ligne, my_char);
	printf ("\033[%d;%dH%c", row+ligne, 1, my_char);
	printf ("\033[%d;%dH|", row+ligne, distance+1);
	fflush(stdout);
	micro_pause.tv_sec = 0;       /* secondes */
	micro_pause.tv_nsec = 1000;   /* nanosecondes */
	nanosleep( &micro_pause ,NULL);

	while (cpt<distance)
	{
		if (read( fileno(stdin), &c,1) && (c==my_char))
		{
			cpt++;
			printf ("\033[%d;%dH %c", row+ligne, cpt,c);    
			fflush(stdout);
			nanosleep( &micro_pause ,NULL);
		}
		nanosleep( &micro_pause ,NULL);
	}
}

int course (int nb_joueurs, int distance)
{
	char tab_car[NB_MAX_JOUEURS]={’a’, ’m’, ’c’, ’n’};
	char *tab_classement [NB_MAX_JOUEURS] = {"\033[31m\033[1mGagnant !\033[0m", "2ème", "3ème", "4ème"};
	char dernier[] = "\033[94mDernier !\033[0m";
	int i;
	pid_t fils[NB_MAX_JOUEURS], fils_termine, exit_fils; 

	fputs("\033[?25l", stdout); 
	printf("\033[H\033[J");
	fflush(stdout);

	if (!Term_non_canonique())
		mon_exit(4);
	for (i=0; i<nb_joueurs; i++)
	{
		switch (fils[i]=fork())
		{
		case -1 : /* Erreur */
			perror("Échec création du fils ");
			mon_exit(3);
		case 0 : /* Fils */
			joueur(tab_car[i], i, distance);
			exit(i);
		}
	}
	i=0;
	while ((fils_termine=wait(&exit_fils))>0)
	{
		printf("\033[%d;%dH ",WEXITSTATUS(exit_fils)+1,11);
		if (i+1<nb_joueurs)
			printf("%s",tab_classement[i]);
		else
			printf("%s",dernier);
		printf ("\033[K");  
		fflush(stdout);
		i++;
	}
	printf("\033[%d;%dH\n",NB_MAX_JOUEURS+nb_joueurs+2,1);

	Term_canonique();
	fputs("\033[?25h", stdout); 

	return 0;
}


int main (int argc, char * argv[])
{
	int nb_joueurs, distance;
    
	if (argc>3)
	{
		fprintf(stderr,"Usage : %s [nb_joueurs] [distance]\n",argv[0]);
		exit(1);
	}
	if (argc == 3)
	{
		nb_joueurs = atoi(argv[1]);
		distance = atoi(argv[2]);
	}
	else if (argc == 2)
	{
		nb_joueurs = atoi(argv[1]);
		distance = 10;
	}
	else
	{
		nb_joueurs = 2;
		distance = 10;
	}


	if (nb_joueurs < 2 || nb_joueurs > NB_MAX_JOUEURS)
	{
		fprintf(stderr,"Usage : %s [nb_joueurs] [distance]\n",argv[0]);
		fprintf(stderr," erreur nb_joueurs doit être inclus dans [2;%d] !\n",NB_MAX_JOUEURS);
		exit(2);
	}
	if (distance < 2 || distance > DISTANCE_MAX)
	{
		fprintf(stderr,"Usage : %s [nb_joueurs] [distance]\n",argv[0]);
		fprintf(stderr," erreur distance doit être inclus dans [2;%d] !\n",DISTANCE_MAX);
		exit(2);
	}

	exit (course(nb_joueurs, distance));
}