#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

void* print_numbers(void* arg){
  int* thread_order = (int*) arg;
  printf("Executing %d-th thread\n", *thread_order);
  for(int i=0; i<5; i++){
    printf("%d ", i);
  }
  printf("\n");
}

int main() {
  pthread_t threads[3];
  int thread_ids[3] = {1, 2, 3};
  
  for (int i = 0; i < 3; i++) {
      if (pthread_create(&threads[i], NULL, print_numbers, &thread_ids[i])) {
        perror("Failed to create thread");
        return 1;
      }
  }
  for (int i = 0; i < 3; i++) {
    if (pthread_join(threads[i], NULL)) {
      perror("Failed to join thread");
      return 1;
    }
  }
}
