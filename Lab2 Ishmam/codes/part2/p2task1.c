// system call diye cmd theke ekta file open kora
// then it will ask user t enter string in that file
// it will ask as long as the user enters "-1"
// if the file is not in the directory, then it will create a new file

#include <stdio.h>
#include <fcntl.h>   // For open()
#include <unistd.h>  // For write(), close()
#include <string.h>  // For strlen()

int main(int arg1, char *arg2[])
{   
    // file er name assign korsi
    if (arg1 != 2)
    {
        printf("Usage: %s <filename>\n", arg2[0]);
        return 1;
    }

    int file_dest = open(arg2[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file_dest == -1)
    {
        printf("File could not be opened\n");
        return 1;
    }

    printf("File '%s' is ready for writing\n", arg2[1]);
    char buff[250];

    while(1){
        printf("Enter a string to write to the text file, enter -1 to exit: ");
        fgets(buff, 250, stdin);

        //new line character remove korsi
        buff[strcspn(buff, "\n")] = 0;

        if (strcmp(buff, "-1") == 0)
        {
            break;
        }

        // write input string to the file
        if (write(file_dest, buff, strlen(buff)) == -1)
        {
            printf("Error writing to file\n");
            close(file_dest);
            return 1;
        }

        // new line character write korsi
        if (write(file_dest, "\n", 1) == -1)
        {
            printf("Error writing to file\n");
            close(file_dest);
            return 1;
        }
    }
    printf("File writing complete\n");
    close(file_dest);
    return 0;

}

