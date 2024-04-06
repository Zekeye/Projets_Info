#define _POSIX_C_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "matrice.c"
#include "traiterLigne.c"

const char *tab[]={"non trouve", "v1 trouve", "v2 trouve", "v1 et V2 trouves"};

int main(int argc, const char *argv[]){
  int matrice[NB_LIGNES_MAX][NB_COLONNES_MAX];
  unsigned int nbLignes, nbColonnes,v1 ,v2;
  unsigned OccRep, nbRep[4], n;
  int i=0;
  pid_t *pid_SousTraitants;

  if (argc!=5){
   fprintf(stderr, "%s Usage: %s nbLignes nb Colonnes v1 v2\n", argv[0], argv [0]);
   exit(1);
  }

  nbLignes=atoi(argv[1]);
  nbColonnes=atoi(argv[2]);
  v1=atoi(argv[3]);
  v2=atoi(argv[4]);

  initialiserMatrice(matrice, nbLignes, nbColonnes);
  afficherMatrice(matrice, nbLignes, nbColonnes);

  pid_SousTraitants = malloc(nbLignes*sizeof(pid_t));
  while(i<nbLignes){
    switch(pid_SousTraitants[i]=fork()){
      case -1: perror("Erreur creation processus");
               exit(2);

      case 0: exit(traiterLigne(matrice[i], nbColonnes, v1, v2));
    }
  }

  OccRep=0;
  while(OccRep<4){
    nbRep[OccRep]=0;
    OccRep+=1;
  }

  n=0;
  while (n!=nbLignes){
    int val_wait;
    pid_t pid_fini=wait(&val_wait);
    
    if (pid_fini != -1){
      n++;

      i=0;
      while(pid_SousTraitants[i]!=pid_fini){
        i++;
      }

      if (WIFEXITED(val_wait)){
        unsigned rep = WEXITSTATUS(val_wait);
        nbRep[rep]++;
        printf("Ligne %u= %s\n", i, tab[rep]);
      }
      else{
        printf("%u: fin sous-traitant\n", i);
      }
    }
  }

  OccRep=0;
  while(OccRep<4){
    printf("%s: %u\n", tab[OccRep], nbRep[OccRep]);
    OccRep+=1;
  }

  return 0;
}

