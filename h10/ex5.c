#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define K 3   // number of printers
#define N 10  // number of print job threads

sem_t printers;
pthread_mutex_t counter_mutex;
int active = 0;      // current active printing threads
int max_active = 0;  

void* print_job(void* arg) {
    long id = (long)arg;

    sem_wait(&printers);

    pthread_mutex_lock(&counter_mutex);
    active++;
    if (active > max_active)
        max_active = active;
    pthread_mutex_unlock(&counter_mutex);

    printf("Thread %ld is printing... (active=%d)\n", id, active);
    usleep(200000); // simulate printing work

    // exit critical section
    pthread_mutex_lock(&counter_mutex);
    active--;
    pthread_mutex_unlock(&counter_mutex);

    sem_post(&printers);
    return NULL;
}

int main() {
    pthread_t threads[N];

    sem_init(&printers, 0, K);
    pthread_mutex_init(&counter_mutex, NULL);

    for (long i = 0; i < N; i++)
        pthread_create(&threads[i], NULL, print_job, (void*)i);

    for (int i = 0; i < N; i++)
        pthread_join(threads[i], NULL);

    printf("Max simultaneously printing (should be ≤ %d): %d\n", K, max_active);

    sem_destroy(&printers);
    pthread_mutex_destroy(&counter_mutex);
}

