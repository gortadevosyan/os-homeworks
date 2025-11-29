#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

long long counter = 0;
int M = 100000;
int N = 4;
pthread_mutex_t mutex; 

void* increment(void* arg) {
    for (long long i = 0; i < M; i++) {
        pthread_mutex_lock(&mutex);
        counter++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
  pthread_mutex_init(&mutex, NULL);
  pthread_t threads[N];

  for (int i = 0; i < N; i++) {
      if (pthread_create(&threads[i], NULL, increment, NULL)) {
        perror("Failed to create thread");
        return 1;
      }
  }
  for (int i = 0; i < N; i++) {
    if (pthread_join(threads[i], NULL)) {
      perror("Failed to join thread");
      return 1;
    }
  }
  printf("Expected output: %d\n", N*M);
  printf("Actual output: %lld\n", counter);
  pthread_mutex_destroy(&mutex);
  return 0;
}

