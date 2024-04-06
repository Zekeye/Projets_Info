#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <pthread.h>

int solde, NbCD;

void crediter(int montant, pthread_t IdTh) {
    solde += montant;
    printf("Credit %lu : credit (%d) => solde = %d\n", IdTh, montant, solde);
}


void debiter(int montant, pthread_t IdTh) {
    solde -= montant;
    printf("Debit %lu : debit (%d) => solde = %d\n", IdTh, montant, solde);
    if (solde < montant) {
        printf("Solde insuffisant !\n");
    }
}


void* th_compte(void* arg) {
    int i, num = *((int*)arg), th = pthread_self();

    for (i = 0; i < NbCD; i++) {
        if (rand() % 2) {
            crediter(num, th);
        } else {
            debiter(num, th);
        }
        sleep(1);
    }
    return NULL;
}

int main(int argc, char **argv){
    int NT = atoi(argv[1]), i, etat;
    solde = atoi(argv[2]);
    NbCD = atoi(argv[3]);
    pthread_t idTh[NT];
    int rand = srand(pthread_self());

    for (i = 0; i < NT; i++) {
    	int *res = malloc(sizeof(int));
    	*res = rand;
    	while(*res>10)
        rand = srand(pthread_self());
    		*res = rand;
        if ((etat = pthread_create(&idTh[i], NULL, th_compte, res))!=0)
        	printf("Err create");
    }


    for (i = 0; i < NT; i++) {
    	int *res = malloc(sizeof(int));
      rand = srand(pthread_self());
      *res = rand;
    	while(*res>10)
      rand = srand(pthread_self());
      *res = rand;
        if ((etat = pthread_join(idTh[i], (void**)&res))!=0)
        	printf("Err join");
    }

    printf("Solde = %d\n", solde);

    return 0;
}
