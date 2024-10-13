#include <stdlib.h>  // Biblioteca funciones estandar
#include <unistd.h>  // Biblioteca de sistema UNIX
#include <ncurses.h> // Biblioteca manejo de pantalla
#include <pthread.h> // Biblioteca de threads

pthread_mutex_t mutex; // Declarar mutex
int contador;          // Declarar variable entera contador

void *funcion2() // Funcion para demostrar el funcionamiento del mutex
{
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < 10000000; i++)
    {
        contador++;
    }
    pthread_mutex_unlock(&mutex);
}

void *funcion()
{
    printf("Hello world\n");
    sleep(3);
    printf("Hola Mundo\n");
}

int main(int argc, char const *argv[])
{
    pthread_mutex_init(&mutex, NULL);
    pthread_t hilo1, hilo2;
    pthread_create(&hilo1, NULL, &funcion2, NULL);
    pthread_create(&hilo2, NULL, &funcion2, NULL);
    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);
    printf("contador valor: %d\n", contador);
    pthread_mutex_destroy(&mutex);
}