#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>


void printStatus(int pid, int status){
    if (WIFEXITED(status)) {
        printf("Child process (PID: %d) exited normally with status1: %d\n", pid, WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("Child process (PID: %d) terminated by signal: %d\n", pid, WTERMSIG(status));
    } else {
        printf("Child process (PID: %d) terminated for unknown reason.\n", pid);
    }
}
int main() {
    int pid1 = fork();

    if(pid1 == 0){
        printf("Child process 1 pid: %d \n", getpid());
        exit(1);
    }

    int pid2 = fork();

    if(pid2 == 0) {
        printf("Child process 2 pid: %d \n", getpid());
        exit(0);
    }

    int status1 = 0;
    waitpid(pid1, &status1, 0);
    printStatus(pid1, status1);

    int status2 = 0;
    waitpid(pid2, &status2, 0);
    printStatus(pid2, status2);

    printf("Parent process finished! \n");
}
