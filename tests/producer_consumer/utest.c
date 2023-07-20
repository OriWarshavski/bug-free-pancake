#include <stdio.h>
#include "producer_consumer.h"
#include "pthread.h"

int main ()
{
    pthread_t t1, t2;
    sem_init(&count_mutex, 0, 1);
    sem_init(&empty, 0, N);
    sem_init(&full, 0, 0);
    pthread_create(&t1, NULL, producer, NULL);
    pthread_create(&t2, NULL, consumer, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
}


