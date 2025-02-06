// write a multithread program to find deficient numbers from 1 to 100, 
//

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define NUM_THREADS 3

void *find_deficient_numbers(void *arg) {
    int start = ((int *)arg)[0];
    int end = ((int *)arg)[1];
    for (int num = start; num <= end; num++) {
        int sum = 0;
        for (int i = 1; i <= num / 2; i++) {
            if (num % i == 0) {
                sum += i;
            }
        }
        if (sum < num) {
            printf("%d ", num);
        }
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int ranges[NUM_THREADS][2] = {{1, 33}, {34, 67}, {68, 100}};
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, find_deficient_numbers, (void *)ranges[i]);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}

