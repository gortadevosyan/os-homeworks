#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

void printStatus(int pid, int status){
    if (WIFEXITED(status)) {
        printf("Child process (PID: %d) exited normally with status: %d\n", pid, WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("Child process (PID: %d) terminated by signal: %d\n", pid, WTERMSIG(status));
    } else {
        printf("Child process (PID: %d) terminated for unknown reason.\n", pid);
    }
}
int main() {
    int pid = fork();

    if (pid == 0){
        printf("Child process: %d \n", getpid());
    }
    else {
        wait(NULL);
        printf("Parent process: %d \n", getpid());

        int pid2 = fork();

        if (pid2 == 0) {
            printf("Nested child process: %d \n", getpid());
        }
        else {
	    int status = 0;
            waitpid(pid2, &status, 0);
            printf("Parent process with waithpid(%d): %d\n", getpid());
	    printStatus(pid2, status);
        }
    }
    return 0;
}
