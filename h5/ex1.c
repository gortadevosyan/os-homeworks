#include <stdio.h>
#include <stdlib.h>
int main() {
 int n;
 printf("Input array length: ");
 scanf("%d", &n);
 int *arr = malloc(n*sizeof(int));
 printf("Enter %d elements: ", n);
 for(int i=0; i<n; i++) {
  scanf("%d", &arr[i]);
 }
 int S = 0;
 for(int i=0; i<n; i++) {
  S += arr[i];
 }
 printf("Array sum: %d\n", S);
 free(arr);
 return 0;
}
