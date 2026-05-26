#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int *buffer;
int BUFFER_SIZE;

int in = 0, out = 0;
int total_items;

sem_t empty, full;
pthread_mutex_t mutex;

void* producer(void* arg) {
    for (int i = 0; i < total_items; i++) {
        int item = i + 1;  // Auto-generate items

        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        printf("[Producer] Produced: %d -> Buffer[%d]\n", item, in);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);

        sleep(1);
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 0; i < total_items; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        int item = buffer[out];
        printf("                [Consumer] Consumed: %d <- Buffer[%d]\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t p, c;

    printf("Enter buffer size: ");
    scanf("%d", &BUFFER_SIZE);

    printf("Enter number of items: ");
    scanf("%d", &total_items);

    buffer = (int*)malloc(sizeof(int) * BUFFER_SIZE);

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    free(buffer);
    return 0;
}

/*
Enter buffer size: 3
Enter number of items: 3
[Producer] Produced: 1 -> Buffer[0]
                [Consumer] Consumed: 1 <- Buffer[0]
[Producer] Produced: 2 -> Buffer[1]
                [Consumer] Consumed: 2 <- Buffer[1]
[Producer] Produced: 3 -> Buffer[2]
                [Consumer] Consumed: 3 <- Buffer[2]
*/
