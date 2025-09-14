#include "stdio.h"
#include <sys/types.h> 
#include <unistd.h> 

int main() {
    int ret = fork();

    if (ret == 0)
        execl("/usr/bin/grep", "grep", "-rin", "main", "text.txt", NULL);
    else
        wait(NULL);

    printf("Parent process completed\n");
    return 0;
}