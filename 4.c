// 6. Deadlock Avoidance Using Semaphores: Implement the
// deadlock-free solution to Dining Philosophers problem to
// illustrate the problem of deadlock and/or starvation that can
// occur when many synchronized threads are competing for
// limited resources


#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5

sem_t forks[N];
sem_t room;    /* allows at most N-1 philosophers to try eating -> no deadlock */

void *philosopher(void *arg) {
    int i = *(int *)arg;

    printf("Philosopher %d is thinking\n", i);
    sleep(1);

    sem_wait(&room);
    sem_wait(&forks[i]);
    sem_wait(&forks[(i + 1) % N]);

    printf("Philosopher %d is eating\n", i);
    sleep(1);

    sem_post(&forks[(i + 1) % N]);
    sem_post(&forks[i]);
    sem_post(&room);

    printf("Philosopher %d finished eating\n", i);

    return NULL;
}

int main() {
    pthread_t p[N];
    int id[N];

    for (int i = 0; i < N; i++){
        sem_init(&forks[i], 0, 1);
    }

    sem_init(&room, 0, N - 1);

    for (int i = 0; i < N; i++) {
        id[i] = i;
        pthread_create(&p[i], NULL, philosopher, &id[i]);
    }
    for (int i = 0; i < N; i++){
        pthread_join(p[i], NULL);
    }

    for ( int i = 0; i < N; i++){
        sem_destroy(&forks[i]);
    }

    sem_destroy(&room);
    return 0;
}