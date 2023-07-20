#pragma once
#include "semaphore.h"

#define N 100

extern sem_t count_mutex;
extern sem_t empty;
extern sem_t full;

extern size_t count;

void* consumer(void* a);
void* producer(void* a); 