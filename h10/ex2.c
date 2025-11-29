#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>

int mode = 0;
long long balance = 0;
int num_increments = 0;
int num_decrements = 0;
int num_steps = 0;
pthread_mutex_t mutex;  
pthread_spinlock_t spinlock;

void* increment_with_mutex(void* arg) {
    for (long long i = 0; i < num_steps; i++) {
        pthread_mutex_lock(&mutex);
        balance++;
        if (mode){
          usleep(100);
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* increment_with_spinlock(void* arg) {
    for (long long i = 0; i < num_steps; i++) {
        pthread_spin_lock(&spinlock);
        balance++;
        if (mode){
          usleep(100);
        }
        pthread_spin_unlock(&spinlock);
    }
    return NULL;
}


void* decrement_with_mutex(void* arg) {
    for (long long i = 0; i < num_steps; i++) {
        pthread_mutex_lock(&mutex);
        balance--;
        if (mode){
          usleep(100);
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}


void* decrement_with_spinlock(void* arg) {
    for (long long i = 0; i < num_steps; i++) {
        pthread_spin_lock(&spinlock);
        balance--;
        if (mode){
          usleep(100);
        }
        pthread_spin_unlock(&spinlock);
    }
    return NULL;
}


double measure_execution_time(void* (*increment_func)(void*), void* (*decrement_func)(void*)) {
    int num_threads = num_increments + num_decrements;
    pthread_t threads[num_threads];
    struct timeval start, end;
    
    // Record start time
    gettimeofday(&start, NULL);

    // Create increment threads
    for (int i = 0; i < num_increments; i++) {
        pthread_create(&threads[i], NULL, increment_func, NULL);
    }

    // Create decrement threads
    for (int i = num_increments; i < num_threads ; i++) {
        pthread_create(&threads[i], NULL, decrement_func, NULL);
    }
    // Join threads
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Record end time
    gettimeofday(&end, NULL);

    // Calculate execution time in milliseconds
    double execution_time = (end.tv_sec - start.tv_sec) * 1000.0;
    execution_time += (end.tv_usec - start.tv_usec) / 1000.0;

    return execution_time;
}

int main(int argc, char** argv){
  if(argc != 6) {
    perror("sync_mechanism, mode, num_increments, num_decrements, num_steps are mandatory arguments");
    return 1;
  }
  char *sync_mechanism = argv[1];
  char *mode_str = argv[2];
  if (!strcmp(mode_str, "short"))
    mode = 0;
  else if (!strcmp(mode_str, "long"))
    mode = 1;
  else {
    perror("mode must be short|long");
    return 1;
  }
  num_increments = atoi(argv[3]);
  num_decrements = atoi(argv[4]);
  num_steps = atoi(argv[5]);
  printf("%s %d %d\n", mode_str, num_increments , num_decrements);
  pthread_mutex_init(&mutex, NULL);
  pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE);

  int t = 0;  
  if (!strcmp(sync_mechanism, "spinlock")){
    pthread_mutex_init(&mutex, NULL);
    t = measure_execution_time(increment_with_spinlock, decrement_with_spinlock);
  }
  else if (!strcmp(sync_mechanism, "mutex")) {
    pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE);
    t = measure_execution_time(increment_with_mutex, decrement_with_mutex);
  }  
  else{
    perror("sync must be spinlock|mutex");
    return 1;
  }

  printf("execution time: %ld, balance: %lld\n", (long int) t, balance);
  return 0;
}
