// Thread synchronization using counting semaphores and mutual
// exclusion using mutex.
// Application to demonstrate: producer-consumer problem with
// counting semaphores and mutex.

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define THREADS 5

sem_t sem;                 /* counting semaphore: max 2 threads inside at once */
pthread_mutex_t lock;      /* mutex: protects shared counter */
int counter = 0;

void *worker(void *arg) {
    int id = *(int *)arg;

    sem_wait(&sem);
    printf("Thread %d entered (semaphore acquired)\n", id);

    pthread_mutex_lock(&lock);
    counter++;
    printf("Thread %d incremented counter to %d\n", id, counter);
    pthread_mutex_unlock(&lock);

    sleep(1);
    printf("Thread %d leaving (semaphore released)\n", id);
    sem_post(&sem);
    return NULL;
}

int main() {
    pthread_t t[THREADS];
    int ids[THREADS], i;

    sem_init(&sem, 0, 2);
    pthread_mutex_init(&lock, NULL);

    for (i = 0; i < THREADS; i++) {
        ids[i] = i + 1;
        pthread_create(&t[i], NULL, worker, &ids[i]);
    }
    for (i = 0; i < THREADS; i++)
        pthread_join(t[i], NULL);

    printf("Final counter value = %d\n", counter);

    sem_destroy(&sem);
    pthread_mutex_destroy(&lock);
    return 0;
}