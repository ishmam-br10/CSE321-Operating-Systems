#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/wait.h>

int main(){
    pid_t child, gc1, gc2, gc3;
    printf("I am parent. My PID is %d\n", getpid());

    // first child
    child = fork();
    if (child == 0){
        printf("I am child. My PID is %d \n", getpid());

        // grand child 1
        gc1 = fork();
        if (gc1 == 0){
            printf("Grandchild 1 Process Id %d\n", getpid());
            return 0;
        }

        wait(NULL);

        // grand child 2
        gc2 = fork();
        if (gc2 == 0){
            printf("Grandchild 2 Process Id %d\n", getpid());
            return 0;
        }
        wait(NULL);

        // grand child 3
        gc3 = fork();
        if (gc3 == 0){
            printf("Grandchild 3 Process Id %d\n", getpid());
            return 0;
        }
        wait(NULL);
    }
    else if(child > 0){
        wait(NULL);
        // printf("I am parent. My PID is %d\n", getpid());
    }
    return 0;

}