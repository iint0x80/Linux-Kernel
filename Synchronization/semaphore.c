#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <syscall.h>

sem_t mutex;
int sharedVariable = 0;

void *incrementFunction(void *arg) 
{
    sem_wait(&mutex);
    printf("Thread: [%lu]\n", syscall(SYS_gettid));
    printf("\t\\___Entering the Critical Region\n");

    //Critical Region
    for (int i = 0; i < 100000; ++i) {
        sharedVariable++;
    }
    printf("\t\\___Exiting the Critical Region\n");

    sem_post(&mutex);
}

int main() {
    sem_init(&mutex, 0, 1);
    pthread_t thread1, thread2;

    // Creating Two Threads That Increment the Shared Variable
    pthread_create(&thread1, NULL, incrementFunction, NULL);
    pthread_create(&thread2, NULL, incrementFunction, NULL);

    // Waits for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Expected result: sharedVariable is not guaranteed to be 200000 due to race condition
    printf("Expected Result: 200000\n");
    printf("Final value of sharedVariable: %d\n", sharedVariable);

    sem_destroy(&mutex);
    return 0;
}
