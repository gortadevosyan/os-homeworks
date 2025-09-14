#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 

int main() {
    int ret = fork();

    if (ret == 0)
        execl("/usr/bin/ls", "ls", NULL);
    else
        wait(NULL);

    ret = fork();

    if(ret == 0)
        execl("/usr/bin/date", "date", NULL);
    else 
        wait(NULL);

    printf("Parent process done\n");
    return 0;
}