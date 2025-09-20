#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

int main(){
    int pid = fork();

    if(pid == 0){
        printf("child pid: %d \n", getpid());
    }
    else {
	waitpid(NULL);
        sleep(100); // added for the zombie process
        printf("Parent process pid: %d \n", getpid());
    }
    return 0;
}
