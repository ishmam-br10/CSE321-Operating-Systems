#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX 10 // producers and consumers can produce and consume up to MAX
#define BUFLEN 6
#define NUMTHREAD 2 /* number of threads */

void *consumer(void *id);
void *producer(void *id);

char buffer[BUFLEN];
char source[BUFLEN]; // from this array producer will store its production into buffer
int pCount = 0;
int cCount = 0;
int buflen;

// initializing pthread mutex and condition variables
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t nonEmpty = PTHREAD_COND_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;

int thread_id[NUMTHREAD] = {0, 1};
int i = 0;
int j = 0;

int main() {
    int i;
    /* define the type to be pthread */
    pthread_t thread[NUMTHREAD];
    strcpy(source, "abcdef");
    buflen = strlen(source);

    /* create 2 threads */
    /* create one consumer and one producer */
    /* define the properties of multi threads for both threads */
    pthread_create(&thread[0], NULL, producer, (void *)&thread_id[0]);
    pthread_create(&thread[1], NULL, consumer, (void *)&thread_id[1]);

    /* wait for the threads to finish */
    for (i = 0; i < NUMTHREAD; i++) {
        pthread_join(thread[i], NULL);
    }

    return 0;
}

void *producer(void *id) {
    {
        while (i<MAX){
            pthread_mutex_lock(&count_mutex);

            while ((pCount + 1) % buflen == cCount) {
                pthread_cond_wait(&full, &count_mutex);
            }
            char p = source[i % buflen];
            buffer[pCount % BUFLEN] = p;
            printf("%d produced %c by Thread %d\n", *thread_id, buffer[pCount], pCount);
            pCount++;
            i++;

            pthread_cond_signal(&nonEmpty);
            pthread_mutex_unlock(&count_mutex);

            sleep(1); // simulate time taken to produce
        }
    }
}

void *consumer(void *id) {
    {
        while(j<MAX){
            pthread_mutex_lock(&count_mutex);

            while (cCount == pCount) {
                pthread_cond_wait(&nonEmpty, &count_mutex);
            }

            printf("%d consumed %c by Thread %d\n", *thread_id, buffer[cCount], cCount);
            cCount++;
            j++;

            pthread_cond_signal(&full);
            pthread_mutex_unlock(&count_mutex);

            sleep(1); // simulate time taken to consume
        }
    }
    // pthread_exit(NULL);
}