#include <stdio.h>
#include <stdlib.h>

struct range{
    int start;
    int end;
};

// perfect number ber kora lagbe. Where, A perfect number is a positive integer that is
// equal to the sum of its proper divisors, excluding itself. 

// perfect number er funtion

int purrfect_number(struct range range){
    printf("The perfect numbers between %d and %d are: \n", range.start, range.end);
    int i;
    
    for(i = range.start; i <= range.end; i++){
        int sum = 0;
        for(int j = 1; j < i; j++){
            if (i % j == 0){
                sum += j;
            }
        }
        if (sum == i){
            printf("%d \n", i);
        }
    }
}

int main(){
    struct range range;
    // start range ar ending range input
    //start range
    printf("Enter the starting range: ");
    scanf("%d", &range.start);
    //ending range
    printf("Enter the ending range: ");
    scanf("%d", &range.end);

    // perfect number ber kora
    purrfect_number(range);
    return 0;

}