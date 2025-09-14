#include "stdio.h"
#include <sys/types.h> 
#include <unistd.h> 

int main() {
    int ret = fork();

    if (ret == 0)
        execl("/usr/bin/echo", "echo", "Hello from the child!", NULL);
    else
        wait(NULL);

    printf("Parent process done\n");
    return 0;
}