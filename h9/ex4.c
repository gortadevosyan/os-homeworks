#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

void* calculate_square(void* arg){
  int* num = (int*) arg;
  printf("Square of %d is %d\n", *num, (*num) * (*num));
  *num = (*num) * (*num);
}

int main() {
  int arr_len = 0;
  printf("Enter the array length: ");
  scanf("%d", &arr_len);
  printf("Enter the array: ");
  int* arr = malloc(arr_len * sizeof(int));
  if(arr == NULL) {
    perror("Malloc failed");
    return 1;  
  }
  for(int i=0; i<arr_len; i++) scanf("%d", &arr[i]);
  
  pthread_t *threads = malloc(arr_len * sizeof(pthread_t));
  if(threads == NULL) {
    perror("Malloc failed");
    return 1;
  }

  for (int i = 0; i < arr_len; i++) {
      if (pthread_create(&threads[i], NULL, calculate_square, &arr[i])) {
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
  return 0;
}
