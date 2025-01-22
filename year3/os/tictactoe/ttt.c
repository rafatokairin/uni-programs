#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t tic;
sem_t tac;
sem_t toe;

void* thread1(void* arg) {
    //wait
    sem_wait(&tic);
    printf("tic-");
    //critical section
    sem_post(&tac);
    return NULL;
}

void* thread2(void* arg) {
    //wait
    sem_wait(&tac);
    printf("tac-");
    //critical section
    sem_post(&toe);
    return NULL;
}

void* thread3(void* arg) {
    //wait
    sem_wait(&toe);
    printf("toe-");
    //critical section
    sem_post(&tic);
    return NULL;
}

void handleTTT(pthread_t *t1, pthread_t *t2, pthread_t *t3) {
    pthread_create(t1,NULL,thread1,NULL);
    pthread_create(t2,NULL,thread2,NULL);
    pthread_create(t3,NULL,thread3,NULL);
    pthread_join(*t1,NULL);
    pthread_join(*t2,NULL);
    pthread_join(*t3,NULL);
}

int main() {
    sem_init(&tic, 0, 1);
    sem_init(&tac, 0, 0);
    sem_init(&toe, 0, 0);

    pthread_t t1,t2,t3;
    handleTTT(&t1,&t2,&t3);

    sem_destroy(&tic);
    sem_destroy(&tac);
    sem_destroy(&toe);
    printf("\n");
}