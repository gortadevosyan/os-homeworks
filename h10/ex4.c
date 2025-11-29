#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define N 10

sem_t semA, semB, semC;

void* thread_A(void* arg) {
    for (int i = 0; i < N; i++) {
        sem_wait(&semA);
        printf("A %d\n", i);
        sem_post(&semB);
    }
    return NULL;
}

void* thread_B(void* arg) {
    for (int i = 0; i < N; i++) {
        sem_wait(&semB);
        printf("B %d\n", i);
        sem_post(&semC);
    }
    return NULL;
}

void* thread_C(void* arg) {
    for (int i = 0; i < N; i++) {
        sem_wait(&semC);
        printf("C %d\n", i);
        sem_post(&semA);
    }
    return NULL;
}

int main() {
    pthread_t a, b, c;

    sem_init(&semA, 0, 1);
    sem_init(&semB, 0, 0);
    sem_init(&semC, 0, 0);

    pthread_create(&a, NULL, thread_A, NULL);
    pthread_create(&b, NULL, thread_B, NULL);
    pthread_create(&c, NULL, thread_C, NULL);

    pthread_join(a, NULL);
    pthread_join(b, NULL);
    pthread_join(c, NULL);

    sem_destroy(&semA);
    sem_destroy(&semB);
    sem_destroy(&semC);
}

