#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
int main() 
{ 
    printf("level 0: Parent process id: %d\n", getpid());
    
    fork();
 
    printf("level 1: process id: %d, parentid: %d \n", getpid(), getppid());
    sleep(1);

    fork();

    printf("level 2: process id: %d, parentid: %d \n", getpid(), getppid());
    sleep(1);
    
    fork();
 
    printf("level 3: process id: %d, parentid: %d \n", getpid(), getppid());
    sleep(1);
    return 0; 
} 