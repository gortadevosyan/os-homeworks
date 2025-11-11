#include <stdio.h>
#include <pthread.h>

void* print_thread_message(){
  pthread_t cur = pthread_self();
  printf("Thread %ld is running\n", cur);
  return NULL;
}

int main(){

  int thread_num = 3;
  pthread_t thread_1, thread_2, thread_3; 
  if(pthread_create(&thread_1, NULL, print_thread_message, NULL) != 0) {
    perror("Failed to create thread");
    return 1;
  }
  if(pthread_create(&thread_2, NULL, print_thread_message, NULL) != 0) {
    perror("Failed to create thread 2");
    return 1;
  }
  if(pthread_create(&thread_3, NULL, print_thread_message, NULL) != 0) {
    perror("Failed to create thread 3");
    return 1;
  }

  if (pthread_join(thread_1, NULL) != 0) {
      perror("Failed to join thread 1");
      return 1;
  }
  if (pthread_join(thread_2, NULL) != 0) {
      perror("Failed to join thread 2");
      return 1;
  }
  if (pthread_join(thread_3, NULL) != 0) {
      perror("Failed to join thread 3");
      return 1;
  }

  return 0;
}
