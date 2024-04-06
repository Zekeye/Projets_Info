#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>

void fils(int rang){
    printf("Activité rang %d : identifiant = %d\n", rang, getpid());
}

void pere(){
    while (wait(NULL)>0);
    exit(1);
}



int main(int argc, char **argv){
    int NA, NF;
    NA=atoi(argv[1]);
    NF=atoi(argv[2]);
    
    if (argc != 3) {
        printf("Usage : %s <\n", argv[0]);
        exit(1);
    }
    
    for(int i = 0; i < NA; i++){
        
        switch (fork()){
          
          case -1 : {
              perror("err");
              exit(0);
          }
          case 0 : {
              for (int j = 0; j < NF; j++){           
              	fils(i);
              	sleep(1);  
              	}
              	     
              printf("Valeur retournee par le fils %d = %d\n", getpid(), i);       
              exit(1);          
          }        
      default : {
          break;      
      }
    }

    }
    pere();    
    return 0;
}
