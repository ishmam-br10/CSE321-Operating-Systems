#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h> 
#include <sys/shm.h>

struct msg {
    long int type;
    char txt[6];
};

int main(){
    printf("Please enter the workspace name: \n");
    char workspace[100];
    scanf("%s", workspace);
    if (strcmp(workspace, "cse321") != 0){
        printf("Invalid workspace name\n");
        exit(1);
    }
    else{
        int message_id;
        struct msg sent;

        message_id = msgget((key_t)1234, 0666 | IPC_CREAT);
        sent.type = 2;
        strncpy(sent.txt, workspace, sizeof(sent.txt));
        msgsnd(message_id, (void *)&sent, sizeof(sent.txt), 0);
        printf("Workspace name sent to otp generator form log in: %s\n", sent.txt);

        pid_t otp_server = fork();
        if (otp_server ==0){
            struct msg received;
            // msgrcv(message_id, (void *)&received, sizeof(received.txt), 1, 0);
            message_id = msgget((key_t)1234, 0666 | IPC_CREAT);
            msgrcv(message_id, (void *)&received, sizeof(received.txt), 2, IPC_NOWAIT);
            printf("OTP generator received workspace name from log in: %s\n", received.txt);
            pid_t pid = getpid();
            char buffer[100];
            struct msg child_wrote;
            child_wrote.type = 5;
            sprintf(buffer, "%d", pid);
            strncpy(child_wrote.txt, buffer, sizeof(child_wrote.txt));
            sent.type = 8;
            strncpy(sent.txt, buffer, sizeof(sent.txt));
            msgsnd(message_id, (void *)&sent, sizeof(sent.txt), 0);
            printf("OTP sent to log in form otp generator: %s\n", sent.txt);

            msgsnd(message_id, (void *)&child_wrote, sizeof(child_wrote.txt), 0);
            printf("OTP sent to mail from otp generator: %s\n", child_wrote.txt);

            pid_t mail_server = fork();
            if (mail_server == 0){
                struct msg mail_received;
                message_id = msgget((key_t)1234, 0666 | IPC_CREAT);
                msgrcv(message_id, (void *)&mail_received, sizeof(mail_received.txt), 5, IPC_NOWAIT);
                printf("Mail received OTP from otp generator: %s\n", mail_received.txt);

                sent.type = 9;
                strncpy(sent.txt, mail_received.txt, sizeof(sent.txt));
                msgsnd(message_id, (void *)&sent, sizeof(sent.txt), 0);
                printf("OTP sent to log in from mail: %s\n", sent.txt);
            }
            else{
                wait(NULL);
            }
        }
        else{
            wait(NULL);
            msgrcv(message_id, (void *)&sent, sizeof(sent.txt), 8, IPC_NOWAIT);
            printf("Log in received OTP from OTP generator: %s\n", sent.txt);
            char otp[30];
            strncpy(otp, sent.txt, sizeof(otp));
            msgrcv(message_id, (void *)&sent, sizeof(sent.txt), 9, IPC_NOWAIT);
            printf("Log in received OTP from mail: %s\n", sent.txt);
            char mail_otp[30];
            strncpy(mail_otp, sent.txt, sizeof(mail_otp));
            if (strcmp(otp, mail_otp) == 0){
                printf("OTP verified\n");
            }
            else{
                printf("OTP did not match\n");
            }
            msgctl(message_id, IPC_RMID, 0);

        }
    }
    return 0;
}