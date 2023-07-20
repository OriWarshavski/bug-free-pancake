#include "producer_consumer.h"
#include "stdio.h"
#include<unistd.h>

size_t count = 0;
sem_t count_mutex;
sem_t empty;
sem_t full;

void* producer(void* a)
{
    while(1) {
        sem_wait(&empty);
        sem_wait(&count_mutex);
        ++count;
        printf("producer working... products:%ld\n", count);
        sem_post(&count_mutex);
        sem_post(&full);
    }
}

void* consumer(void* a)
{
    while(1) {
        sem_wait(&full);
        sem_wait(&count_mutex);
        --count;
        printf("consumer buying... remaining products:%ld\n", count);
        sem_post(&count_mutex);
        sem_post(&empty);
    }
}