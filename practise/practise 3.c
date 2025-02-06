//
#include <stdio.h>
#include <stdlib.h>
int main(){
    char arr1[] = {'a', 'b', 'c', 'd'};
    char arr2[] = {'b', 'd', 'e'};
    char arr3[] = {};
    // find the elements that are in arr2 but not in arr1
    int found;
    int k = 0;
    for (int i = 0; i < sizeof(arr2); i++) {
        found = 0;
        for (int j = 0; j < sizeof(arr1); j++) {
            if (arr2[i] == arr1[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            arr3[k++] = arr2[i];
        }
    }
    arr3[k] = '\0'; // Null-terminate the result array

    // Print the result
    printf("Elements in arr2 but not in arr1: ");
    for (int i = 0; i < k; i++) {
        printf("%c ", arr3[i]);
    }
    printf("\n");
}