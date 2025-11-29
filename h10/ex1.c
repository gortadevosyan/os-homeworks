#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

long long counter = 0;
int M = 100000;
int N = 4;

void* increment(void* arg) {
  for(int i=0; i<M; i++)
    counter++;
  return NULL;
}

int main() {
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
  return 0;
}

