//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    int fd = open("git_log.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("Failed to open file");
        exit(1);
    }


    write(fd, "Codebase change log for codebase 1.\n", 36);

    pid_t pid1 = fork();
    if (pid1 == 0) {
        // First child process
        int num1;
        printf("Child 1: Enter a number: \n");
        scanf("%d", &num1);
        dprintf(fd, "%d\n", num1);
        close(fd);
        exit(0);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        // Second child process
        int num2;
        printf("Child 2: Enter a number: \n");
        scanf("%d", &num2);
        dprintf(fd, "%d\n", num2);
        close(fd);
        exit(0);
    }

    // Parent process
    wait(NULL);
    wait(NULL);

    lseek(fd, 0, SEEK_SET);
    char buffer[256];
    int num1, num2;
    read(fd, buffer, sizeof(buffer));
    sscanf(buffer, "Codebase change log for codebase 1.\n%d\n%d\n", &num1, &num2);

    int total = num1 + num2;
    dprintf(fd, "Total number of commits: %d\n", total);

    close(fd);
    return 0;
}