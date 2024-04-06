#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <pthread.h>

int NF;

void afficher (int rang, pthread_t IdTh){
    printf("Thread %d : mon identificateur est %d\n", rang, IdTh);
}


void *affichage_th (void *arg) {
    int i, num = *((int *) arg), th = pthread_self();

    for (i = 0; i < NF; i++)
        afficher(num, th);

    free(arg);
    pthread_exit(NULL);
}



int main(int argc, char **argv){
    int NA, etat, i;
    pthread_t idTh[10];
    NA=atoi(argv[1]);
    NF=atoi(argv[2]);

    if (argc != 3) {
        printf("Usage : %s <\n", argv[0]);
        exit(1);
    }

    for(i = 0; i < NA; i++){
    	int *res = malloc(sizeof(int));
        *res = i;
        if ((etat = pthread_create(&idTh[i], NULL, affichage_th, res)) != 0)
            printf("Echec create");
    }
    
    for (i = 0; i < NA; i++) {
        int *res = malloc(sizeof(int));
        if ((etat = pthread_join(idTh[i], (void**)&res)) != 0)
           printf("Echec join");
        printf("Valeur retournee par le thread %d = %d\n", idTh, i);
    }
    return 0;
}
