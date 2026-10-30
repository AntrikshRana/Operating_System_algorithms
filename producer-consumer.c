/* Q10: Producer-Consumer Problem using semaphores (POSIX threads)
   Compile: gcc q10_producer_consumer.c -o q10 -pthread */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;
int total_items;

sem_t empty_slots;   /* counts free slots in buffer   */
sem_t full_slots;    /* counts filled slots in buffer */
sem_t mutex;         /* mutual exclusion on buffer    */

void *producer(void *arg) {
    for (int i = 1; i <= total_items; i++) {
        sem_wait(&empty_slots);          /* wait for a free slot */
        sem_wait(&mutex);                /* enter critical section */

        buffer[in] = i;
        printf("Producer produced item %d at position %d\n", i, in);
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex);                /* leave critical section */
        sem_post(&full_slots);           /* signal an item is available */
        usleep(100000);
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 1; i <= total_items; i++) {
        sem_wait(&full_slots);           /* wait for an item */
        sem_wait(&mutex);

        int item = buffer[out];
        printf("    Consumer consumed item %d from position %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&empty_slots);          /* signal a slot is free */
        usleep(250000);
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    printf("Enter number of items to produce: ");
    scanf("%d", &total_items);

    sem_init(&empty_slots, 0, BUFFER_SIZE);
    sem_init(&full_slots, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&empty_slots);
    sem_destroy(&full_slots);
    sem_destroy(&mutex);

    printf("\nAll items produced and consumed successfully.\n");
    return 0;
}