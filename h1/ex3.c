#include "stdio.h"

void swap(int* a, int* b){
    int c = *a;
    *a = *b;
    *b = c;
}

int main(){
    int a = 5;
    int b = 8;

    printf("before: %d, %d \n", a, b);

    swap(&a, &b);

    printf("after: %d, %d \n", a, b);

    return 0;
}