#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
int main() 
{ 
    printf("pid: %d \n", getpid());
	int ret = fork();

    if (ret == 0) 
        execl("/usr/bin/ls", "ls", NULL);
    else {
        wait(NULL);  
        printf("parent process done\n");
    }
    
    return 0; 
} 