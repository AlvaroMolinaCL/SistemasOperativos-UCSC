#include <stdio.h>   // Para printf y scanf
#include <pthread.h> // Para usar hilos pthread_t
#include <string.h>  // Para usar strcpy
#include <unistd.h>  // Para usar sleep
#include <stdlib.h>  // Para usar rand y srand
#include <time.h>    // Para usar time

// Datos para la hebra
struct datos
{
    int id;
    char nombre[100];
    int distanciaRecorrida;
};

// Distancia total de la carrera
#define DISTANCIA_TOTAL 100

// Variable para indicar si la carrera ha terminado
int carreraTerminada = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Punto de entrada de hilo
void *hebra_caballo(void *arg)
{
    struct datos *dato = (struct datos *)arg;
    while (dato->distanciaRecorrida < DISTANCIA_TOTAL && !carreraTerminada)
    {
        // Simula el avance del caballo
        int avance = rand() % 10 + 1; // Avanza entre 1 y 10 unidades
        dato->distanciaRecorrida += avance;
        printf("Caballo %s ha avanzado a %d metros\n", dato->nombre, dato->distanciaRecorrida);

        // Espera un tiempo aleatorio entre 0 y 1 segundo
        usleep((rand() % 100) * 10000);

        // Verifica si el caballo ha terminado la carrera
        pthread_mutex_lock(&mutex);
        if (dato->distanciaRecorrida >= DISTANCIA_TOTAL && !carreraTerminada)
        {
            carreraTerminada = 1;
            printf("El caballo %s ha ganado la carrera!\n", dato->nombre);
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

// Punto de entrada del programa
int main(int argc, char const *argv[])
{
    srand(time(NULL)); // Inicializa la semilla para los números aleatorios

    // Crear y inicializar datos para los caballos
    struct datos caballos[5];
    char *nombres[] = {"Rayo", "Centella", "Trueno", "Relampago", "Tormenta"};

    for (int i = 0; i < 5; i++)
    {
        caballos[i].id = i + 1;
        strcpy(caballos[i].nombre, nombres[i]);
        caballos[i].distanciaRecorrida = 0;
    }

    pthread_t hebras[5]; // Se declaran los hilos

    // Se asocia un hilo a una función
    for (int i = 0; i < 5; i++)
    {
        pthread_create(&hebras[i], NULL, hebra_caballo, &caballos[i]);
    }

    // Lanza los hilos
    for (int i = 0; i < 5; i++)
    {
        pthread_join(hebras[i], NULL);
    }

    return 0;
}