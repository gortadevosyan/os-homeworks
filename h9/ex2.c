#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

int arr[] = {1};
int arr_len = 1;
typedef struct thread_struct {
  int start;
  int end;
  int* arr;
  int sum;
} ThreadStruct;

void* calculate_array_sum(void* arg) {
  ThreadStruct* ts =  (ThreadStruct*)arg;
  int s = 0;
  for(int i=ts->start; i<=ts->end; i++){
    s += (ts->arr)[i];
  }
  ts->sum = s;
}
int main(){
  pthread_t thread_1, thread_2;
  ThreadStruct st1, st2;
  
  int arr_len;
  printf("enter the array length\n");
  scanf("%d", &arr_len);
  int* arr = malloc(arr_len * sizeof(int)); 
  if ( arr == NULL) {perror("Malloc failed"); return(1);}

  printf("enter the array\n");
  for(int i=0; i<arr_len; i++){
    scanf("%d", &arr[i]); 
  }

  st1.start = 0, st1.end = (arr_len - 1) / 2;
  st1.arr = arr, st1.sum = 0;
  st2.start = (1 + arr_len)/2, st2.end = arr_len - 1;   
  st2.arr = arr, st2.sum = 0;
   
  if( pthread_create(&thread_1, NULL, calculate_array_sum, (void*)&st1)) {perror("Failed to create thread 1"); return 1;}
  if( pthread_create(&thread_2, NULL, calculate_array_sum, (void*)&st2)) {perror("Failed to create thread 2"); return 1;}
  
  if (pthread_join(thread_1, NULL)){
    perror("Failed to join thread 1");
    return 1;
  }
  if (pthread_join(thread_2, NULL)){
    perror("Failed to join thread 2");
    return 1;
  }
  printf("partial sum 1: %d\n", st1.sum);
  printf("partial sum 2: %d\n", st2.sum);
  return 0;
}
