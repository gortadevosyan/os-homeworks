#include "stdio.h"
#include <unistd.h>

int main() {
    int ret = fork();

    if (ret == 0) {
        printf("child process: %d \n", getpid());
    }
    else {
        printf("parent process: %d \n", getpid());
    }

    return 0;
}