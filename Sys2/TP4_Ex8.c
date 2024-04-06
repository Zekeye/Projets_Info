#define _POSIX_C_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>


#define LONG_MAX_NOM      20
typedef struct{
	char Nom[LONG_MAX_NOM+1];
	int Age;
	int NbEnfants;
} Infos;

/* Lecture d'un entier tapé au clavier */
int LireEntier(void)
{
  int n;

  while(scanf("%d",&n)!=1)
  {
    printf("? ");
    fflush(stdout);
    while (getchar()!='\n');
  }
  return n;
}


int Creation(char NomFichier[]){
	int fd;
	Infos info;

	fd=open(NomFichier, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);

	if (fd==-1){
		perror("Echec ouverture ecriture");
		return 1;
	}

	while(1){
		
		printf("f pour terminez saisie\n");
		printf("Nom ?\n");
		fflush(stdout);
		scanf("%s", info.Nom);
		
		if(info.Nom[0]=='f'){
			break;
		}
		
		printf("Age ?\n");
		fflush(stdout);
		info.Age=LireEntier();
		
		printf("Nombre d'enfants ?\n");
		fflush(stdout);
		info.NbEnfants=LireEntier();

		write(fd, &info, sizeof(info));
	}

	

	close(fd);
	return 0;
}


int main(void){
	char titre[]="fichier";
	Creation(titre);
	return 0;
}
