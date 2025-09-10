#include "stdio.h"

int main(){
    int a = 5;
    int* p = &a;

    printf("%p \n", &a);
    printf("%p \n", p);

    *p = 10;

    printf("new value: %d \n", a);
}