#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define cantidad_threads 4

sem_t semaforo1;
pthread_t threads[cantidad_threads];
int agua = 0;
pthread_mutex_t mutex_agua;

void *funcion(void *args)
{
    pthread_mutex_lock(&mutex_agua);
    sem_wait(&semaforo1);
    int sem_valor;
    sem_getvalue(&semaforo1, &sem_valor);
    printf("Semáforo decrementa su contador a %d \n", sem_valor);
    agua = agua + 50;
    printf("Valor agua %d litros \n", agua);
    sem_post(&semaforo1);
    pthread_mutex_unlock(&mutex_agua);
    sem_getvalue(&semaforo1, &sem_valor);
    printf("Semáforo incrementa contador a %d \n", sem_valor);
}

int main(int argc, char const *argv[])
{
    pthread_mutex_init(&mutex_agua, NULL);
    sem_init(&semaforo1, 0, 4);
    for (int i = 0; i < cantidad_threads; i++)
    {
        pthread_create(&threads[i], NULL, &funcion, NULL);
    }
    for (int i = 0; i < cantidad_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }
    sem_destroy(&semaforo1);
    pthread_mutex_destroy(&mutex_agua);
    return 0;
}