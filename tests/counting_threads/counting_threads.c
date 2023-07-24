#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

#define N 1000
#define IS_ODD(NUM) (NUM % 2)

int count = 0;
sem_t odd, even;

static void* counting_odd_v1(void* a)
{
    while(1) {
        sem_wait(&odd);
        if(IS_ODD(count)) {
            printf("odd: %d\n", count);
            ++count;
        }
        sem_post(&even);
        if(count == N)
        {
            break;
        }
    }
    return NULL;
}

static void* counting_even_v1(void* a)
{
    while(1) {
        sem_wait(&even);
        if(!IS_ODD(count)) {
            printf("even: %d\n", count);
            ++count;
        }
        sem_post(&odd);
        if(count == N + 1)
        {
            break;
        }
    }
    return NULL;

}

pthread_cond_t even_cond;
pthread_cond_t odd_cond;
pthread_mutex_t mtx;

void* counting_odd_v2(void* arg) {
    for (int i = 1; i < N; i += 2) {
        pthread_mutex_lock(&mtx);
        printf("odd: %d\n", i);
        pthread_cond_signal(&even_cond);
        if(i < N) {
            pthread_cond_wait(&odd_cond, &mtx);
        }
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

void* counting_even_v2(void* arg) {
    for (int i = 0; i <= N; i += 2) {
        pthread_mutex_lock(&mtx);
        printf("even: %d\n", i);
        pthread_cond_signal(&odd_cond);
        if(i < N) {
            pthread_cond_wait(&even_cond, &mtx);
        }
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

int printEven = 1;

void* counting_odd_v3(void* arg) {
    for (int i = 1; i < N; i += 2) {
        while(printEven);
        printf("odd: %d\n", i);
        if(i < N) {
            printEven = 1;
        }
    }
    return NULL;
}

void* counting_even_v3(void* arg) {
    for (int i = 0; i <= N; i += 2) {
        while(!printEven);
        printf("even: %d\n", i);
        if(i < N) {
            printEven = 0;
        }
    }
    return NULL;
}

static void test_v1();
static void test_v2();
static void test3_spinLock();

int main()
{
    test_v1();
    test_v2();
    test3_spinLock();


    return 0;
}

static void test_v1()
{
    pthread_t oddT, evenT;
    sem_init(&odd, 0, 1);
    sem_init(&even, 0, 1);
    pthread_create(&evenT, NULL, counting_even_v1, NULL);
    pthread_create(&oddT, NULL, counting_odd_v1, NULL);

    pthread_join(oddT, NULL);
    pthread_join(evenT, NULL);
    sem_destroy(&odd);
    sem_destroy(&even);

    if(count == 1001)
	{
		printf("Test V1 ......................................PASS\n");
	}
	else
	{
		printf("Test V1 ......................................FAIL\n");
	}
}

static void test_v2()
{
    pthread_t odd, even;
    pthread_mutex_init(&mtx, NULL);
    pthread_cond_init(&even_cond, NULL);
    pthread_cond_init(&odd_cond, NULL);

    pthread_create(&even, NULL, counting_even_v2, NULL);
    pthread_create(&odd, NULL, counting_odd_v2, NULL);

    pthread_join(odd, NULL);
    pthread_join(even, NULL);

	printf("Test V2 ......................................PASS\n");

}

static void test3_spinLock()
{
    pthread_t oddTh, evenTh;
    pthread_create(&evenTh, NULL, counting_even_v3, NULL);
    pthread_create(&oddTh, NULL, counting_odd_v3, NULL);

    pthread_join(evenTh, NULL);
    pthread_join(oddTh, NULL);

	printf("Test V3 ......................................PASS\n");

}