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

int Consultation(char NomFichier[]){
	int fd;
	Infos info;
	int NumFiche, pos_fiche, NbFichesFichier;
	
	fd=open(NomFichier, O_RDONLY);

	if (fd==-1){
		perror("Echec lecture fichier");
		return 1;
	}
	
	NbFichesFichier=lseek(fd,0,SEEK_END)/sizeof(info);
	printf("%d fiches dans le fichier.\n", NbFichesFichier);
	
	while(1){
		do{
			printf("0 pour interrompre la lecture\n");
		
			printf("Numero de fiche ?\n");
			fflush(stdout);
			NumFiche=LireEntier();
		}while (NumFiche<0 || NumFiche>NbFichesFichier);
		if (NumFiche==0){
			printf("Fin de consultation des fiches\n");
			break;
		}
		

		pos_fiche=(NumFiche-1)*sizeof(info);
		lseek(fd, pos_fiche, SEEK_SET);
		read(fd, &info, sizeof(info));
		
		printf("Numero Fiche : %d\n", NumFiche);
		printf("Nom : %s\n Age : %d\n Nombre d'enfants %d\n", info.Nom, info.Age, info.NbEnfants);
		printf(" \n");
		
	}

	close(fd);
	return 0;
}
	




int main(void){
	char titre[]="fichier";
	Consultation(titre);
	return 0;
}
