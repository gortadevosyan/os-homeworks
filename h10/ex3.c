#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
#include <sys/time.h>

#define TOTAL_ITEMS 100
#define BUFFER_SIZE 8
#define PRODUCER_COUNT 4
#define CONSUMER_COUNT 2
int buffer[BUFFER_SIZE];
int in_pos = 0;
int out_pos = 0;
int items_to_produce = TOTAL_ITEMS;

sem_t empty_slots;
sem_t full_slots;
pthread_mutex_t buffer_mutex;

void print_buffer(){
  for(int i=0; i<BUFFER_SIZE; i++){
    printf("%d", buffer[i]);
  }
  printf("\n");
}

void* produce(void* arg) {
  while (1) {
    sem_wait(&empty_slots);
    pthread_mutex_lock(&buffer_mutex);
    if (items_to_produce <= 0){
      pthread_mutex_unlock(&buffer_mutex);
      break;   
    }
    buffer[in_pos] = 1;
    items_to_produce--;
    in_pos = (in_pos + 1) % BUFFER_SIZE;
    pthread_mutex_unlock(&buffer_mutex);
    sem_post(&full_slots);
  }
  return NULL;
}

void* consume(void* arg) {
  while (1) {
    sem_wait(&full_slots);
    pthread_mutex_lock(&buffer_mutex);
   
    // should finish and signal the rest 
    int item_value = buffer[out_pos];
    if (item_value == -1) {
        pthread_mutex_unlock(&buffer_mutex);
        sem_post(&full_slots); 
        break;
    }
    buffer[out_pos] = 0;
    print_buffer();
    out_pos = (out_pos + 1) % BUFFER_SIZE;
    pthread_mutex_unlock(&buffer_mutex);
    sem_post(&empty_slots);
  }
    return NULL;
}



int main() {
  sem_init(&empty_slots, 0, BUFFER_SIZE);
  sem_init(&full_slots, 0, 0);
  pthread_mutex_init(&buffer_mutex, NULL);
  pthread_t producers[PRODUCER_COUNT];
  pthread_t consumers[CONSUMER_COUNT];
  for (int i = 0; i < PRODUCER_COUNT; i++)
    pthread_create(&producers[i], NULL, produce, NULL);
  for (int i = 0; i < CONSUMER_COUNT; i++)
    pthread_create(&consumers[i], NULL, consume, NULL);

  for (int i = 0; i < PRODUCER_COUNT; i++)
    pthread_join(producers[i], NULL);

  for (int i = 0; i < CONSUMER_COUNT; i++) {
      sem_wait(&empty_slots); 
      
      pthread_mutex_lock(&buffer_mutex);
      buffer[in_pos] = -1; // Poison pill logic
      in_pos = (in_pos + 1) % BUFFER_SIZE;
      pthread_mutex_unlock(&buffer_mutex);
      sem_post(&full_slots);
  }

  for (int i = 0; i < CONSUMER_COUNT; i++)
    pthread_join(consumers[i], NULL);

  sem_destroy(&full_slots);
  sem_destroy(&empty_slots);
}
