#include "stdio.h"

int main(){
    int arr[] = {1, 2, 3, 4, 5};

    printf("before: ");
    for(int i=0; i<5; i++){
        printf("%d ", *(arr+i));
    }

    printf("\nafter: \nusing pointer:");

    *(arr + 2) = 6;
    for(int i=0; i<5; i++){
        printf("%d ", *(arr+i));
    }
    printf("\nusing regular array");
    for(int i=0; i<5; i++){
        printf("%d ", arr[i]);
    }
}