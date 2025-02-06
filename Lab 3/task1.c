#include <stdio.h>       
#include <stdlib.h>      
#include <string.h>      
#include <unistd.h>      
#include <sys/types.h>  
#include <sys/shm.h>     
#include <sys/ipc.h>     
#include <sys/wait.h>

// create structure
struct shared{
    char sel[100];
    int b;
};

int main(){
    int piper[2];
    char buffer[100];

    if (pipe(piper) == -1){
        // perror("pipe");
        printf("Pipe failed\n");
        exit(1);
    }
    int shared_memory_id;
    struct shared *shared_memory;
    shared_memory_id = shmget((key_t)1234, sizeof(struct shared), 0666 | IPC_CREAT);
    shared_memory = (struct shared *)shmat(shared_memory_id, NULL, 0);
    shared_memory->b = 1000;
    printf("Provide Your Input from Given Options:\n");
    printf("1. Type a to Add Money\n");
    printf("2. Type w to Withdraw Money\n");
    printf("3. Type c to Check Balance\n");
    char selection[100];
    scanf("%s", selection);
    printf("Your selection: %s\n", selection);
    strcpy(shared_memory->sel, selection);
    pid_t pid = fork();
    if (pid == 0){
        close(piper[0]);
        struct shared *child_shared_memory;
        child_shared_memory = (struct shared *)shmat(shared_memory_id, NULL, 0);

        char selection[100];
        int money;
        strcpy(selection, child_shared_memory->sel);

        if (strcmp(selection, "a") == 0){
            printf("Enter the amount to be addes: \n");
            scanf("%d", &money);
            if (money < 0){

                printf("Adding failed, Invalid amount\n");
                // exit(1);
            }
            else{
                child_shared_memory->b += money;
                printf("Money added successfully\n");
                printf("Updated balance after addition: %d\n", child_shared_memory->b);
            }
        }
        else if(strcmp(selection, "w") == 0){
            printf("Enter the amount to be withdrawn: \n");
            scanf("%d", &money);
            if (money < 0){
                printf("Withdraw failed, Invalid amount\n");
                exit(1);
            }
            else if (money > child_shared_memory->b){
                printf("Withdraw failed, Insufficient balance\n");
                // exit(1);
            }
            else{
                child_shared_memory->b -= money;
                printf("Balance withdrawn successfully\n");
                printf("Updated balance after withdrawal: %d\n", child_shared_memory->b);
            }
        }
        else if(strcmp(selection, "c") == 0){
            printf("Current balance: %d\n", child_shared_memory->b);
        }
        else{
            printf("Invalid selection\n");
            // exit(1);
    
        }
        strcpy(buffer, "Thank you for using.\n");
        write(piper[1], buffer, strlen(buffer)+1);
        close(piper[1]);

    }
    else{
        // int temp;
        // wait(&temp);
        wait(NULL);
        close(piper[1]);
        read(piper[0], buffer, sizeof(buffer));
        printf("%s\n", buffer);
        close(piper[0]);
    }
    return 0;
}
