#include <stdio.h>
#include <stdlib.h>

void printArray(int* arr, int n, char *message){
 printf("%s", message);
 for(int i=0; i<n; i++)
  printf("%d ", arr[i]);
 printf("\n");
}

int main() {
 int n;
 printf("Input array length: ");
 scanf("%d", &n);
 int *arr = calloc(n, sizeof(int));
 printArray(arr, n, "Array after calloc: ");
 //printf("Array after calloc: ");
 //for(int i=0; i<n; i++)
 // printf("%d ", arr[i]);

 printf("Enter %d elements: ", n);
 for(int i=0; i<n; i++) {
  scanf("%d", &arr[i]);
 }
 printArray(arr, n, "Updated array: ");
 int S = 0;
 for(int i=0; i<n; i++) {
  S += arr[i];
 }
 double average = (S+0.0)/n;
 printf("Average of the array: %f\n", average);
 free(arr);
 return 0;
}
