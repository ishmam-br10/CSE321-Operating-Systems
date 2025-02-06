#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


void odd_process(pid_t pid, int *process){
    if (pid % 2 != 0){
        // printf("I am odd process \n");
        pid_t new = fork();
        if (new == 0){
            *process = *process + 1;
        }
        else if (new > 0)   
        {
            wait(NULL);
            // printf("I am parent \n");
        }
        
    }
}

int main(){
    int process = 1;
    pid_t a, b, c;

    a = fork();
    if (a == 0){
        process = process + 1;
        odd_process(getpid(), &process);
    }
    else if(a> 0){
        //wait for die
        wait(NULL);
        process = process + 1;
    }

    b = fork();
    if (b == 0){
        process = process + 1;
        odd_process(getpid(), &process);
    }
    else if(b> 0){
        wait(NULL);
        process = process + 1;
    }

    c = fork();
    if (c == 0){
        process = process + 1;
        odd_process(getpid(), &process);
    }
    else if(c> 0){
        wait(NULL);
        process = process + 1;
    }

    // if (a > 0 && b > 0 && c > 0){
    //     // printf("I am parent \n");
    //     printf("Total number of processes created: %d \n", process);
    // }
    printf("Total number of processes created: %d \n", process);
}