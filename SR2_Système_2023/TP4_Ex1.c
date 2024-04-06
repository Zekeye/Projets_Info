#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>

#define NB_THREAD_MAX 20

typedef struct {
    int rang;
    int NBT;
    int NBM;
    int NBL;
    pthread_mutex_t *mutex;
    int *compteur;
} parametres;

void attenteAleatoire(int rang) {
    usleep((rand() % 100) * (rang + 1));
}

void P(pthread_mutex_t *mutex) {
    pthread_mutex_lock(mutex);
}

void V(pthread_mutex_t *mutex) {
    pthread_mutex_unlock(mutex);
}

void* afficher(void *arg) {
    int i, j;
    parametres p = *(parametres *)arg;

    srand(pthread_self());

    for (i = 0; i < p.NBM; i++) {
        P(p.mutex);

        while (*p.compteur != p.rang) {
            V(p.mutex);
            P(p.mutex);
        }

        for (j = 0; j < p.NBL; j++) {
            printf("Afficheur %d (Thread ID%lu), j'affiche ligne %d/%d du message %d/%d\n",
                   p.rang, pthread_self(), j, p.NBL, i, p.NBM);
            attenteAleatoire(p.rang);
        }

        *p.compteur = (*p.compteur + 1) % p.NBT;
        V(p.mutex);
    }

    printf("Afficheur %d (Thread ID%lu), je me termine\n", p.rang, pthread_self());
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    pthread_t th_aff[NB_THREAD_MAX];
    parametres param[NB_THREAD_MAX];
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    int compteur = 0;
    int i, etat, nbThreads, nbLignes, nbMessages;

    if (argc != 4) {
        printf("Usage : %s\n", argv[0]);
        exit(1);
    }

    nbThreads = atoi(argv[1]);
    nbLignes = atoi(argv[2]);
    nbMessages = atoi(argv[3]);
    if (nbThreads > NB_THREAD_MAX)
        nbThreads = NB_THREAD_MAX;

    for (i = 0; i < nbThreads; i++) {
        param[i].rang = i;
        param[i].NBT = nbThreads;
        param[i].NBM = nbMessages;
        param[i].NBL = nbLignes;
        param[i].mutex = &mutex;
        param[i].compteur = &compteur;
        if ((etat = pthread_create(&th_aff[i], NULL, afficher, &param[i])) != 0) {
            fprintf(stderr, "Erreur lors de la creation du thread %d : %s\n", i, strerror(etat));
            exit(1);
        }
    }

    for (i = 0; i < nbThreads; i++) {
        if ((etat = pthread_join(th_aff[i], NULL)) != 0) {
            fprintf(stderr, "Erreur lors de l'attente du thread %d : %s\n", i, strerror(etat));
            exit(1);
        }
    }

    printf("Fin de l'execution du thread principal\n");
    return 0;
}
