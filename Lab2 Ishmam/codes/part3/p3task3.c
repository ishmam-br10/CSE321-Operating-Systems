#include <stdio.h>
#include <pthread.h> // For threads
#include <unistd.h>  // For sleep()
#include <string.h>

#define users 3

// ascii sum er array
int sum[users] = {0};

// calculate ascii sum

void* ascii_sum(void *arg){
    char *name = (char *)arg;
    int sum = 0;
    for (int i = 0; i < strlen(name); i++){
        sum += name[i];
    }
    printf("%s : %d\n", name, sum);
    return (void *)(size_t)sum;
}

void* checker(void *arg){
    if (sum[0] == sum[1] && sum[0] == sum[2]){
        printf("Youreaka! \n");
    }
    else if ((sum[0] == sum[1]) || sum[0] == sum[2] || sum[1] == sum[2]){
        printf("Miracle! \n");
    }
    else{
        printf("Hasta la vista! \n");
    }
    return NULL;
}

int main(){
    pthread_t threads[users + 1];
    char names[users][50];
    for (int i = 0; i< users; i++){
        printf("Enter a name:");
        scanf("%s", names[i]);
        printf("\n");
    }

    for (int i = 0; i < users; i++){
        pthread_create(&threads[i], NULL, ascii_sum, (void *)names[i]);
    }

    for (int i = 0; i < users; i++){
        void* temp;
        pthread_join(threads[i], &temp);
        sum[i] = (int)(size_t)temp;
    }

    pthread_create(&threads[users], NULL, checker, NULL);
    pthread_join(threads[users], NULL);
    return 0;
}
