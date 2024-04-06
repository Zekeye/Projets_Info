#define _POSIX_C_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


/* Exercice 1 
Question 1
*/

void affiche_info(){
  printf("ID processus : %d\n", getpid());
  printf("ID processus père : %d\n", getppid());
  printf("ID processus groupe : %d\n", getpgrp());
  printf("------------------------------------------------------------------------------\n");
  printf("Login : %s\n", getlogin());
  printf("UID : %d\n", getuid());
  printf("GID : %d\n", getgid());
  printf("------------------------------------------------------------------------------\n");
}

int main(void){
  pid_t pid_fils;
  int circonstance;
  pid_fils=fork();

  if(pid_fils==-1){
    perror("forte");
    exit(1);
  }
  
  else if (pid_fils){
  printf("Info père :\n");
  affiche_info();
  printf("------------------------------------------------------------------------------\n");
  wait(&circonstance);
  printf("Terminaison processus père de pid %d et code de retour du fils %d. Code retour père : %d\n",  
         getpid(), WEXITSTATUS(circonstance), EXIT_SUCCESS);
  exit(EXIT_SUCCESS);
  }

  else{
    printf("Info fils :\n");
    affiche_info();
    printf("Terminaison processus fils de pid %d et code de retour : %d\n",  
           getpid(), EXIT_SUCCESS);
    exit(EXIT_SUCCESS);
  }
    
  
  return 0;
}


