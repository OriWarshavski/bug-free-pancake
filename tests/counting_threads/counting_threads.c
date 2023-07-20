#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

#define N 1000
#define IS_ODD(NUM) (NUM % 2)

int count = 0;
sem_t mutex;

// static void* counting_odd_v1(void* a)
// {
//     while(1) {
//         sem_wait(&mutex);
//         if(IS_ODD(count)) {
//             printf("odd: %d\n", count);
//             ++count;
//         }
//         sem_post(&mutex);
//         if(count == N)
//         {
//             break;
//         }
//     }
//     return NULL;
// }

// static void* counting_even_v1(void* a)
// {
//     while(1) {
//         sem_wait(&mutex);
//         if(!IS_ODD(count)) {
//             printf("even: %d\n", count);
//             ++count;
//         }
//         sem_post(&mutex);
//         if(count == N + 1)
//         {
//             break;
//         }
//     }
//     return NULL;

// }

pthread_cond_t even_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t odd_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

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


// static void test_v1();
static void test_v2();

int main()
{
    /*test_v1();*/
    test_v2();

    return 0;
}

// static void test_v1()
// {
//     pthread_t odd, even;
//     sem_init(&mutex, 0, 1);
//     pthread_create(&even, NULL, counting_even_v1, NULL);
//     pthread_create(&odd, NULL, counting_odd_v1, NULL);

//     pthread_join(odd, NULL);
//     pthread_join(even, NULL);
//     sem_destroy(&mutex);

//     if(count == 1001)
// 	{
// 		printf("Test V1 ......................................PASS\n");
// 	}
// 	else
// 	{
// 		printf("Test V1 ......................................FAIL\n");
// 	}
// }

static void test_v2()
{
    pthread_t odd, even;
    // pthread_mutex_init(&mtx, NULL);
    // pthread_cond_init(&even_cond, NULL);
    // pthread_cond_init(&odd_cond, NULL);

    pthread_create(&even, NULL, counting_even_v2, NULL);
    pthread_create(&odd, NULL, counting_odd_v2, NULL);

    pthread_join(odd, NULL);
    pthread_join(even, NULL);

}