#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#define FJFS "First Come First Served (FCFS)"
#define SJF "Shortest Job First (SJF)"


typedef struct process {
 int pid;
 int arrival_time;
 int burst_time;
 int turnaround_time;
 int waiting_time;
 int response_time;
} Process;

int process_comparator(const void *a, const void *b){
 const Process *procA = (const Process *)a;
 const Process *procB = (const Process *)b;
 
 int dif = procA->arrival_time - procB->arrival_time;
 return dif ? dif : procA->burst_time - procB->burst_time;
}

void printAlgoName(int type) {
 printf("=== %s ===\n", type ? FJFS : SJF);
}

void printOrder(Process *processes, int n){
 printf("Gantt Chart: |");
 for(int i=0; i<n; i++){
  printf(" P%d |", processes[i].pid);
 }
 printf("\n");
}

void printStructure(){
 printf("PID     AT     BT     WT     TAT    RT\n");
}

void printStatistics(Process *processes, int n){
 for(int i=0; i<n; i++){
  printf("%d       %d      %d      %d      %d      %d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time, processes[i].response_time);
 }
}

void fillStatistics(Process *processes, int n, double *avg_wt, double *avg_tt, double *avg_rt){
 int current_time = 0; 

 for(int i=0; i<n; i++){
  int start_time = current_time;
  if (processes[i].arrival_time > start_time) {
   start_time = processes[i].arrival_time;
  }
  processes[i].waiting_time = start_time - processes[i].arrival_time;
  processes[i].response_time = processes[i].waiting_time;
  int completion_time = start_time + processes[i].burst_time;
  processes[i].turnaround_time = completion_time - processes[i].arrival_time;
  current_time = completion_time;
  *avg_wt += processes[i].waiting_time;
  *avg_tt += processes[i].turnaround_time;
  *avg_rt += processes[i].response_time;
 }
 *avg_wt = *avg_wt / (n + 0.0);
 *avg_tt = *avg_tt / (n + 0.0);
 *avg_rt = *avg_rt / (n + 0.0);
}

void printGantt(Process *processes, int n, int type, double avg_wt, double avg_tt, double avg_rt) {
 printAlgoName(type);
 printOrder(processes, n);
 printStructure();
 printStatistics(processes, n);
 printf("Average Waiting Time: %f\n", avg_wt); 
 printf("Average Turnaround Time: %f\n", avg_tt);
 printf("Average Response Time: %f\n", avg_rt);
}

void fcfs(Process processes[], int n){
 qsort(processes, n, sizeof(Process), process_comparator);
 double avg_wt = 0, avg_tt = 0, avg_rt = 0;
 fillStatistics(processes, n, &avg_wt, &avg_tt, &avg_rt);
 printGantt(processes, n, 1, avg_wt, avg_tt, avg_rt);
}

void sjf(Process processes[], int n){
 qsort(processes, n, sizeof(Process), process_comparator);

 int current_time = processes[0].arrival_time;
 int closest_arrival = current_time;
 _Bool *completed = calloc(n, sizeof(_Bool));
 if (completed == NULL){
  perror("calloc failed");
  return;
 }
 int completed_count = 0;
 double avg_wt = 0, avg_tt = 0, avg_rt = 0;

 while(completed_count < n) {
  int next = -1;
  int min_bt = INT_MAX;
  for(int i=0; i<n; i++) {
   if (processes[i].arrival_time > current_time) {
    closest_arrival = processes[i].arrival_time;
    break;
   }
   if (!completed[i] && processes[i].burst_time < min_bt) {
    next = i;
    min_bt = processes[i].burst_time;
   }
  }
  
  if(next == -1){
   current_time = closest_arrival;
   continue;
  }
  processes[next].waiting_time = current_time - processes[next].arrival_time; 
  completed[next] = true;
  current_time += processes[next].burst_time;  
  processes[next].turnaround_time = current_time - processes[next].arrival_time; 
  processes[next].response_time = processes[next].waiting_time;
  completed_count++;
  avg_wt += processes[next].waiting_time;
  avg_tt += processes[next].turnaround_time;
  avg_rt += processes[next].response_time;
 }

 avg_wt = avg_wt / (n + 0.0);
 avg_tt = avg_tt / (n + 0.0);
 avg_rt = avg_rt / (n + 0.0);
 printGantt(processes, n, 0, avg_wt, avg_tt, avg_rt);
 free(completed);
}

int main(){
 int n;
 printf("Enter the number of processes:");
 scanf("%d", &n);
 printf("\n");

 Process *processes = malloc(n*sizeof(Process));
 if (processes == NULL) {
  perror("Failed to allocate memory");
  return 1;
 }
 for(int i=0; i<n; i++){
  Process proc;
  printf("Enter the arrival time and busrt time for process %d:", i);
  scanf("%d %d", &proc.arrival_time, &proc.burst_time); 
  proc.pid = i+1;
  processes[i] = proc;
  printf("\n");
 }
 // not passing by reference since both algorithms change the input data
 fcfs(processes, n);
 printf("\n");
 sjf(processes, n);
 free(processes);
 return 0;
}
