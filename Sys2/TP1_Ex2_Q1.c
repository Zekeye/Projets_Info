#define _POSIX_C_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define NBMOTSMAX 20
/* Construction d'un tableau de pointeurs vers le d�but des mots d'une chaine
 * de caract�res en vue de l'utilisation de la fonction execvp.
 * Retourne le nombre de mots trouves.
 */
int Decoupe(char Chaine[], char *pMots[])
{
  char *p;
  int NbMots=0;

  p=Chaine; /* On commence par le d�but */
  /* Tant que la fin de la cha�ne n'est pas atteinte et qu'on ne d�borde pas */
  while ((*p)!='\0' && NbMots<NBMOTSMAX)
  {
    while ((*p)==' ' && (*p)!='\0') p++; /* Recherche du d�but du mot */
    if ((*p)=='\0') break; /* Fin de cha�ne atteinte */
    pMots[NbMots++]=p; /* Rangement de l'adresse du 1er caract�re du mot */
    while ((*p)!=' ' && (*p)!='\0') p++; /* Recherche de la fin du mot */
    if ((*p)=='\0') break; /* Fin de cha�ne atteinte */
    *p='\0'; /* Marquage de la fin du mot */
    p++; /* Passage au caract�re suivant */
  }
  pMots[NbMots]=NULL; /* Derni�re adresse */
  return NbMots;
}

int main (int argc, char *argv []){
  pid_t pid_fils;
  int i;
  char *pMots[NBMOTSMAX+1];
  
  
  
  for (i=1; i<argc; i++){
    pid_fils=fork();
    
    if (pid_fils==-1){
      perror("Echec creation fils");
      exit(1);
    }
    
    else if (pid_fils){
      printf("[%d] J'ai délégué %s à %d. J'attends sa fin...\n", getpid(), argv[i], pid_fils);
      pid_fils=wait(NULL);
      printf("[%d] %d terminé.\n", getpid(), pid_fils);
    }

    else {
      printf("[%d] Je lance %s :\n", getpid(), argv[i]);
      Decoupe(argv[i], pMots);
      execvp(pMots[0], pMots);
      perror("Echec execvp");
      exit(2);

    }
  }
   printf("[%d] J'ai fini.\n", getpid());
   exit(0);
}
      
     
  
