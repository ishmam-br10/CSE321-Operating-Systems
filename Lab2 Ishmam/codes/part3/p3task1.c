#include <stdio.h>
#include <pthread.h> // For threads
#include <unistd.h>  // For sleep()

// Thread function
void* make_thread(void *arg){
    int *t_arg = (int *)arg;
    printf("Thread %d is running\n", *t_arg);
    sleep(2);
    printf("Thread %d is done\n", *t_arg);
    return NULL;
}

int main(){
    pthread_t threads[5];
    int t_arguments[5] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++){
        pthread_create(&threads[i], NULL, make_thread, (void *)&t_arguments[i]);
        // thread killer
        pthread_join(threads[i], NULL);
    }
    return 0;
}