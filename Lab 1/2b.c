#include <stdio.h>
#include <ctype.h>

int main(){
    FILE *f1, *f2;
    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");
    char ch, prevch = ' ';
    // Read the input file
    while ((ch = fgetc(f1)) != EOF)
    {
        //output file e lekhbo jodi edi space na hou
        if ((isspace(ch) && isspace(prevch)) == 0)
        {
            fputc(ch, f2);
        }
        prevch = ch;
    }
    fclose(f1);
    fclose(f2);
    printf("Ajaira Spaces Has been Removed !\n");
}