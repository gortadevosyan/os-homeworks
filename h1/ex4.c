#include "stdio.h"

int main(){
    int a = 5;
    int *p = &a;
    int **dp = &p;

    printf("pointer: %d\n", *p);
    printf("double pointer: %d \n", **dp);
}