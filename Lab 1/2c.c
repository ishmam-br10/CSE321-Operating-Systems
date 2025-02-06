#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int main(){
    char password[100];
    // checker
    bool Lower = false, Upper = false, Digit = false, Special = false;
    // pass input
    printf("Enter the password: ");
    scanf("%s", password);

    for(int i = 0; i < strlen(password); i++){
        // jodi thake tahole seita true kore dibo
        if (islower(password[i])){
            Lower = true;
        }
        else if (isupper(password[i])){
            Upper = true;
        }
        else if (isdigit(password[i])){
            Digit = true;
        }
        else if (strchr("_$#@", password[i])){
            Special = true;
            
        }
    }
    // check kore dekhbo je password thik ache kina
    if (Lower && Upper && Digit && Special){
        printf("OK\n");
    }
    // jodi na thake tahole ki missing ache ta dekhabe
    else{
        // lower nai
        if(!Lower){
            printf("Lowercase character missing\n");
        }
        // upper nai
        if(!Upper){
            printf("Uppercase character missing\n");
        }
        // digit nai
        if(!Digit){
            printf("Digit missing\n");
        }
        // special nai
        if(!Special){
            printf("Special character missing\n");
        }
        
    }
}