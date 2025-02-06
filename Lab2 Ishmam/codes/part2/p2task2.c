#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t child, grandchild;
    child = fork();

    if (child == 0){
        // eita child process
        // child er vetore je hobe se grandchild hobe
        grandchild = fork();

        if (grandchild == 0){
            printf("I am grandchild \n");
        }

        else{
            wait(NULL);
            printf("I am child \n");
        }

    }
    
    else{
        wait(NULL);
        printf("I am parent \n");
    }

    return 0;
}