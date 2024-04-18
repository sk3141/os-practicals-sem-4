#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE 10
#define THREAD_NUMBER 2

int buffer[BUFFER_SIZE];
sem_t semEmpty; // Number of Empty Slots available in buffer
sem_t semFull; // Number of Slots of buffer that are full
int count = 0; // Point of production or consumption in buffer

void *producer (void *args)
{
    while (1) {
        sleep(1);
        int x = rand() % 100;
        sem_wait(&semEmpty);
        buffer[count] = x;
        count++;
        sem_post(&semFull);
        printf("Produced %d\n", x);
    }
}

void *consumer (void* args)
{
    int y;
    for (int i = 0; i < 5; i++)
    {   
        sem_wait(&semFull);
        y = buffer[count - 1];
        count--;
        printf("Conusmed %d\n", y);
        sem_post(&semEmpty);
    }
}

int main()
{
    srand(time(NULL));
    pthread_t threads[THREAD_NUMBER];
    sem_init(&semEmpty, 0, 10);
    sem_init(&semFull, 0, 0);
    int i;

    for (i = 0; i < THREAD_NUMBER; i++)
    {
        if (i % 2 == 0)
        {
            if (pthread_create(&threads[i], NULL, &producer, NULL) != 0)
            {
                perror("Failed to create Producer thread\n");
            }
        } else {
            if (pthread_create(&threads[i], NULL, &consumer, NULL) != 0)
            {
                perror("Failed to create Consumer Thread\n");
            }
        }
    }

    for (i = 0; i < THREAD_NUMBER; i++)
    {
        if (pthread_join(threads[i], NULL) != 0)
        {
            perror("Failed to join thread\n");
        }
    }
    sem_destroy(&semEmpty);
    sem_destroy(&semFull);
    return 0;
}