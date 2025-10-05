#include <stdio.h>
#include <stdlib.h>

void string_array_realloc(int start, int end, char **arr) {
 for(int i=start; i<end; i++){
  arr[i] = malloc(50*sizeof(char));
  if(arr[i] == NULL) {
   for(int j=0; j<i; j++){
    free(arr[j]);
   }
   free(arr);
   printf("Memory allocation failed for element %d", i);
  }
  scanf("%s", arr[i]);
 }
}

int main() {
 // allocate the initial memory
 char **arr = malloc(3*sizeof(char*));
 if(arr == NULL){
  printf("Memory allocatoin failed");
  return 0;
 }

 printf("Enter 3 strings: ");
 // take the input
 string_array_realloc(0, 3, arr);

 //print the first version with 3 elements
 for(int i=0; i<3; i++){
  printf("array %dth element: %s \n", i, arr[i]);
 }

 // reallocate memory
 char **new_arr = realloc(arr, 5*sizeof(char*));
 if(new_arr == NULL)
  printf("Reallocation failed\n");
 arr = new_arr;

 printf("Enter 2 more strings: ");
 // reallocate for strings
 string_array_realloc(3, 5, arr);

 for(int i=0; i<5; i++) {
  printf("Final array %dth element: %s\n", i, arr[i]);
 }
}
