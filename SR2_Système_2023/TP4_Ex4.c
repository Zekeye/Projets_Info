#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t barriere;
sem_t mutex;
int c = 0, N;

void *th(void *arg) {
    int th_id = *((int *)arg);

    printf("Thread %d (%lu): J'effectue un traitement en parallèle avec les autres\n", c, th_id);

    sem_wait(&mutex);
    printf("Thread %d (%lu): J'arrive au RdV\n", c, th_id);
    c++;

    if (c == N) {
        printf("Thread %d (%lu): Je suis le dernier au RdV\n", c, th_id);
        for (int i = 0; i < N - 1; i++) {
            sem_post(&barriere);
            printf("Thread %d (%lu): Je passe le point de RdV\n", i, th_id);
            printf("Thread %d (%lu): Je continue un traitement en parallèle avec les autres\n", i, th_id);
        }
    } else {
        printf("Thread %d (%lu): Je ne suis pas le dernier au RdV\n", c, th_id);
    }
    sem_post(&mutex);

    sem_wait(&barriere);

    printf("\n");
    printf("\nFin de l'éxécution du thread principal");
    return NULL;
}

int main(int argc, char **argv) {
    N = atoi(argv[1]);
    pthread_t threads[N];

    if (argc < 2) {
        printf("Usage: %s <nombre_threads>\n", argv[0]);
        return 1;
    }


    sem_init(&barriere, 0, 0);
    sem_init(&mutex, 0, 1);

    for (int i = 0; i < N; i++) {
        pthread_create(&threads[i], NULL, th, &threads[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&barriere);
    sem_destroy(&mutex);

    return 0;
}
