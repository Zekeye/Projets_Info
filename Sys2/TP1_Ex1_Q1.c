#define _POSIX_C_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


/* Exercice 1 
Question 1_2
*/

void affiche_info(){
  printf("ID processus : %d\n", getpid());
  printf("ID processus groupe : %d\n", getpgrp());
  printf("Login : %s\n", getlogin());
  printf("UID : %d\n", getuid());
  printf("GID : %d\n", getgid());
}

int main(void){
  affiche_info();
  return 0;
}


