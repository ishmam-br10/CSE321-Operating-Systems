#include <stdio.h>
int main(){
    int a, b, c;
    // input nicchi
    printf("Enter the value of a: ");
    scanf("%d", &a);
    printf("Enter the value of b: ");
    scanf("%d", &b);
    // conditions
    // first number greater than the second one
    if(a > b){
        c = a - b;
        printf("The substraction result is: %d\n", c);
    }
    // second number greater than the first one
    else if(a < b){
        c = b + a;
        printf("The addition result is: %d\n", c);
    }
    else{
        printf("Both numbers are equal\n");
        c = b * a;
        printf("The multiplication result is: %d\n", c);
    }
}