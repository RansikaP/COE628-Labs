#include <stdio.h> /* printf */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* get_pid */
#include <stdlib.h>     /* exit, EXIT_FAILURE */
#include <sys/wait.h>  /* wait */
#include <pthread.h>
#include <sys/stat.h>

void * count(void *);
int globalNumber = 0;
//Create a mutex
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

int main(void) {
    int i;
    pthread_t counterThread[5];

    //Create the 5 threads
    for (i = 0; i < 5; i++) {
        if(pthread_create(&counterThread[i], NULL, &count, NULL)) {
            printf("Thread creation failed: %d\n", i);
        }
    }
    
    //Wait for all treads to finish
    while(globalNumber < 50);
    for (i = 0; i < 5; i++)
        pthread_join(counterThread[i], NULL);    
    
    pthread_mutex_destroy(&mutex1);
    
    return (0);
}

void * count(void * junk) {
    int loopCount = 0;
    pthread_mutex_lock(&mutex1);
    while (loopCount < 10) {
        int tmpNumber = globalNumber;
        printf("counter: %d, Thread: %ld, PID: %d\n",
                tmpNumber, pthread_self(), getpid());
        tmpNumber = globalNumber;
        tmpNumber++;
        usleep(random() % 2);
        globalNumber = tmpNumber;
        loopCount++;
    }
    pthread_mutex_unlock(&mutex1);
    return (0);
}

