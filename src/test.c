#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 5
#define INCREMENTS  100000

typedef struct {
    int *num;
    pthread_mutex_t *lock;
} ThreadData;

void *increment(void *arg)
{
    ThreadData *data = (ThreadData *)arg;
    for (int i = 0; i < INCREMENTS; i++)
    {
        pthread_mutex_lock(data->lock);
        (*data->num)++;
        pthread_mutex_unlock(data->lock);
    }
    return NULL;
}

int main(void)
{
    pthread_t threads[NUM_THREADS];
    int value = 0;
    pthread_mutex_t lock;
    ThreadData tdata;

    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        perror("pthread_mutex_init");
        return 1;
    }

    tdata.num = &value;
    tdata.lock = &lock;

    printf("Before: %d\n", value);

    for (int i = 0; i < NUM_THREADS; i++)
    {
        if (pthread_create(&threads[i], NULL, increment, &tdata) != 0)
        {
            perror("pthread_create");
            return 1;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        if (pthread_join(threads[i], NULL) != 0)
        {
            perror("pthread_join");
            return 1;
        }
    }

    printf("After: %d\n", value);

    pthread_mutex_destroy(&lock);
    return 0;
}
