#include <stdio.h>
#include <stdlib.h>

int main() {
 int *arr = malloc(10*sizeof(int));
 printf("Enter 10 integers: ");
 for(int i=0; i<10; i++)
  scanf("%d", &arr[i]);
 int *arr_new = realloc(arr, 5*sizeof(int));
 if(arr_new == NULL) {
  printf("Reallocation failed\n");
  return 0;
 }
 arr = arr_new;
 printf("Array after resizing: ");
 for(int i=0; i<5; i++)
  printf("%d ", arr[i]);
 printf("\n");
 free(arr_new);
}
