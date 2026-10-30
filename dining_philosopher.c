#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5
#define MEALS 2

sem_t chopstick[N];   /* one semaphore per chopstick */
sem_t room;           /* limits philosophers at the table to N-1 */
pthread_mutex_t print_lock = PTHREAD_MUTEX_INITIALIZER;

void say(int id, const char *msg) {
    pthread_mutex_lock(&print_lock);
    printf("Philosopher %d %s\n", id + 1, msg);
    pthread_mutex_unlock(&print_lock);
}

void *philosopher(void *arg) {
    int id = *(int *)arg;
    int left = id, right = (id + 1) % N;

    for (int m = 0; m < MEALS; m++) {
        say(id, "is thinking");
        usleep(100000 + id * 20000);

        say(id, "is hungry");
        sem_wait(&room);                 /* enter the dining room */
        sem_wait(&chopstick[left]);      /* pick up left chopstick */
        sem_wait(&chopstick[right]);     /* pick up right chopstick */

        say(id, "is eating");
        usleep(200000);

        sem_post(&chopstick[right]);     /* put down chopsticks */
        sem_post(&chopstick[left]);
        sem_post(&room);
        say(id, "finished eating and put down chopsticks");
    }
    return NULL;
}

int main() {
    pthread_t t[N];
    int id[N];

    for (int i = 0; i < N; i++) sem_init(&chopstick[i], 0, 1);
    sem_init(&room, 0, N - 1);

    for (int i = 0; i < N; i++) {
        id[i] = i;
        pthread_create(&t[i], NULL, philosopher, &id[i]);
    }
    for (int i = 0; i < N; i++) pthread_join(t[i], NULL);

    for (int i = 0; i < N; i++) sem_destroy(&chopstick[i]);
    sem_destroy(&room);

    printf("\nAll philosophers have finished eating. No deadlock occurred.\n");
    return 0;
}