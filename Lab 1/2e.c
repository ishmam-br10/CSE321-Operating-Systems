#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
    char pal[100];
    printf("Enter a string: ");
    scanf("%s", pal);
    // pointer ekta string er first e
    const char *start = pal;
    // pointer ekta string er last e
    const char *end = pal + strlen(pal) - 1;

    while (start < end){
        // palindrome er jonno first and last char check korbo
        if (tolower(*start) != tolower(*end)){
            printf("Not a palindrome\n");
            return 0;
        }
        start += 1;
        end -= 1;
    }
    printf("Palindrome\n");
}