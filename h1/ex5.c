#include "stdio.h"

int main(){
    char str[] = "Hello";
    char *p = str;
    char *ep;
    for(int i = 0; i < 5; i++){
        printf("%c", *(p + i));
        ep = p + i;
    }

    printf("\nlength is: %d \n", (int) ((ep-p)/sizeof(char) + 1));
}