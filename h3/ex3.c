#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void exit_scenario_1(){
    printf("exit scenario 1 executed!\n");
}

void exit_scenario_2(){
    printf("exit scenario 2 executed!\n");
}
int main() {
    if (atexit(exit_scenario_1)){
        printf("atexit 1 failed");
    }

    if (atexit(exit_scenario_2)){
        printf("atexit 2 failed! \n");
    }
    exit(0);
    printf("Normal termination! \n");
    return 0;

}