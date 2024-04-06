#define _POSIX_C_SOURCE 199309L /* Pour respecter la norme POSIX 199309 */
#include <stdio.h> /* Pour printf et perror */
#include <stdlib.h> /* Pour exit , EXIT_SUCCESS et EXIT_FAILURE */
#include <sys/types.h> /* Pour pid_t */
#include <unistd.h> /* Pour fork, getpid et sleep */
#include <sys/wait.h> /* Pour wait et WEXITSTATUS */
#include <sys/termios.h> /* le terminal non canonique */
#include <time.h> /* Pour nanosleep */
#include <sys/file.h>
#include <sys/stat.h>
#include <string.h>

#define NB_MAX_JOUEURS 4
#define DISTANCE_MAX 40
#define FICHIER_MONITEUR "my_monitor.dat"

int Term_non_canonique ()
{
	struct termios term;
	tcgetattr( fileno(stdin), &term);/* lit les flags du terminal dans term */
	term.c_lflag &= ~ICANON; /* mode non-canonique */
	term.c_lflag &= ~ECHO; /* supprime l’écho */
	term.c_cc[VMIN] = 1; /* nombre min de caractères */
	term.c_cc[VTIME] = 1; /* latence (timeout) 1/10e de seconde (0: pas de latence) */
	if (tcsetattr( fileno(stdin), TCSANOW, &term) < 0) /* écrit les flags depuis term */
	{
		perror("Term_non_canonique: problème d’initialisation ");
		return 0;
	}
	return 1;
}

/* Term_canonique =====================================
// Mode normal du clavier: lecture par ligne et écho.
//===================================================*/

int Term_canonique ()
{
	struct termios term;
				/* retour en mode ligne */
	tcgetattr( fileno(stdin), &term);/* lit les flags du terminal dans term */
	term.c_lflag |= ICANON; /* mode canonique */
	term.c_lflag |= ECHO; /* rétablit l’écho */
	if (tcsetattr( fileno(stdin), TCSANOW, &term) < 0) /* écrit les flags depuis term */
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
	fflush(stdout);
	unlink(FICHIER_MONITEUR);
	exit(exit_value);
}

void moniteur_de_course(int fd_monitor, char tab_car[], int nb_joueurs, int distance)
{
	int i;
	int position[NB_MAX_JOUEURS];
	char affichage[1024], affiche_un_joueur [128];
	int row=NB_MAX_JOUEURS+2;
	struct timespec micro_pause;
	micro_pause.tv_sec = 0; 
	micro_pause.tv_nsec = 2000;

	for (i=0; i<nb_joueurs; i++)
	{
	printf ("\033[%d;%dH", i+1, 1);
	printf("joueur %u : tapez %c", i, tab_car[i]);
	printf ("\033[%d;%dH|", row+i, distance+1);
	}
	fflush(stdout);

	while (1)
	{
		nanosleep( &micro_pause ,NULL);
		if (lseek(fd_monitor, 0, SEEK_SET)<0)
		{
			perror(FICHIER_MONITEUR);
			exit(NB_MAX_JOUEURS);
		}
		read(fd_monitor, position, sizeof(int)*nb_joueurs);
		affichage[0]=’\0’;
		for (i=0; i<nb_joueurs; i++)
		{ 				
			sprintf(affiche_un_joueur, "\033[%d;%dH\033[1K %c", row+i, position[i],
									tab_car[i]);
			strcat(affichage, affiche_un_joueur);
		}
		fputs(affichage, stdout);
		fflush(stdout);
	}
	exit(0);
}

void joueur(int fd_monitor, int i, char my_char, int distance)
{
	int c;
	int cpt=0;
	struct timespec micro_pause;

	micro_pause.tv_sec = 0; 
	micro_pause.tv_nsec = 10000; 
	nanosleep( &micro_pause ,NULL);

	while (cpt<distance)
	{
		if (read( fileno(stdin), &c,1) && (c==my_char))
		{
			cpt++;
			if (lseek(fd_monitor, sizeof(int)*i, SEEK_SET)<0)
			{
				perror(FICHIER_MONITEUR);
				exit(NB_MAX_JOUEURS);
			}
			write(fd_monitor, &cpt, sizeof(int));
			nanosleep( &micro_pause ,NULL);
		}
		nanosleep( &micro_pause ,NULL);
	}
}

int course (int nb_joueurs, int distance)
{
	char tab_car[NB_MAX_JOUEURS]={’a’, ’m’, ’c’, ’n’};
	char *tab_classement [NB_MAX_JOUEURS] = {"\033[31m\033[1mGagnant !\033[0m", "2ème ",
						"3ème ", "4ème "};
	char dernier[] = "\033[94mDernier !\033[0m";
	int i, zero=0, exit_fils;
	pid_t fils[NB_MAX_JOUEURS], fils_termine; 
	char affichage[1024];
	int fd_monitor;
	pid_t monitor;

	fputs("\033[?25l", stdout); 
	printf("\033[H\033[J");
	fflush(stdout);

	fd_monitor = open(FICHIER_MONITEUR, O_RDWR|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
	if (fd_monitor < 0)
	{
		perror(FICHIER_MONITEUR);
		mon_exit(5);
	}
	for (i=0; i<nb_joueurs; i++)
		if (write(fd_monitor, &zero, sizeof(int))<sizeof(int))
		{
			perror(FICHIER_MONITEUR);
			close(fd_monitor);
			mon_exit(5);
		}

	monitor = fork();
	if (monitor == -1)
	{
		perror("Échec création du fils ");
		close(fd_monitor);
		mon_exit(3);
	}
	else if (!monitor){
		moniteur_de_course(fd_monitor, tab_car, nb_joueurs, distance);
		exit(0);
	}

	if (!Term_non_canonique())
	{
		close(fd_monitor);
		mon_exit(4);
	}

	for (i=0; i<nb_joueurs; i++)
	{
		switch (fils[i]=fork())
		{
	case -1 : /* Problème */
		perror("Échec création du fils : ");
		mon_exit(3);
	case 0 : /*  fils */
		joueur(fd_monitor, i, tab_car[i], distance);
		exit(i);
	/* default : */ /* père */
		}
	}
	i=0;
	while (((fils_termine=wait(&exit_fils))>0) && (WEXITSTATUS(exit_fils) <nb_joueurs))
	{
		if (i+1<nb_joueurs)
			sprintf(affichage,"\033[%d;%dH %s",WEXITSTATUS(exit_fils)+1,11,tab_classement[i]);
		else
			sprintf(affichage,"\033[%d;%dH %s",WEXITSTATUS(exit_fils)+1,11,dernier);
		fputs(affichage, stdout);
		fflush(stdout);
		i++;
		if (i == nb_joueurs)
		{
			kill(monitor, SIGINT); 
			wait(NULL); 
		}
	}
	printf("\033[%d;%dH\n",NB_MAX_JOUEURS+nb_joueurs+2,1);

	close(fd_monitor);
	unlink(FICHIER_MONITEUR);
	Term_canonique();
	fputs("\033[?25h", stdout); /
	fflush(stdout);

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
