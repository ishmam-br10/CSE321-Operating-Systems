#include <stdio.h>
#include <string.h>

int main(){
    char email[100];
    // mail input
    printf("Enter the email: ");
    scanf("%s", email);
    // email er domain er porer part tuku ekta string e save korbo
    char *domain = strchr(email, '@');
    // printf(strcmp(domain, "@kaaj.com"));
    //check kore dekhbo je email thik ache kina
    if (strcmp(domain, "@sheba.xyz") == 0){
        printf("Email address is okay\n");
    }
    // jodi na thake tahole invalid
    else {
        printf("Email address is outdated\n");
    }
}