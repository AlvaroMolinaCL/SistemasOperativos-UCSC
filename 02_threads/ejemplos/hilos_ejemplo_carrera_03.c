#include <stdlib.h>  // Biblioteca funciones estandar
#include <unistd.h>  // Biblioteca de sistema UNIX
#include <ncurses.h> // Biblioteca manejo de pantalla
#include <pthread.h> // Biblioteca de threads

struct CaballoObject // Struct que contendra atributos de caballo
{
    char nombre[20];
    int pos;
};

struct CaballoThreadInfo // Struct que contendra los atributos del hilo para monitorear globalmente la carrera
{
    struct CaballoObject *caballo;
    int numVueltas;
    int longitudPista;
    int vuelta;
    int pos;
};

void *funcionCaballo(void *args) // Funcion de tipo puntero void el cual recibe como argumento otro puntero
                                 // Esta sera la funcion a ejecutar por los hilos
{
    struct CaballoThreadInfo *threadInfo = args;           // Se inicializa nuevamente un struct para almacenar el parametro de la funcion
    struct CaballoObject caballo = *(threadInfo->caballo); // Se asigna el struct de caballo correspondiente a un nuevo struct de tipo caballo
    char *nombre = caballo.nombre;
    int vuelta = 1;
    // Ejemplo de uso del MUTEX (bloquear y desbloquear seccion critica del programa)
    pthread_mutex_lock(&mutex);
    printf("%s vuelta %d\n", nombre, vuelta);
    pthread_mutex_unlock(&mutex);
    free(threadInfo); // Libera la memoria de los atributos del hilo al finalizar la carrera de caballos
    return NULL;
}

pthread_mutex_t mutex; // Declaracion de nuevo MUTEX

int main(int argc, char const *argv[])
{

    int numCaballos = 5;
    struct CaballoObject caballos[numCaballos]; // Crear e Inicializar cada caballo en este ciclo for
    for (int i = 0; i < numCaballos; i++)
    {
        sprintf(caballos[i].nombre, "Cab%d", i + 1);
        caballos[i].pos = 0;
        printf("caballo: %s con posicion %d\n", caballos[i].nombre, caballos[i].pos);
    }

    pthread_t threads[numCaballos]; // Creacion de n cantidad de hilos
    for (int i = 0; i < numCaballos; i++)
    {                                                                                    // For para inicializar atributos para cada hilo
        struct CaballoThreadInfo *threadInfo = malloc(sizeof(struct CaballoThreadInfo)); // Inicializacion de struct tipo puntero con su tamaño de memoria
        threadInfo->caballo = &caballos[i];                                              // A continuacion se accede a cada atributo y se le asigna un valor (Segun enunciado)
        threadInfo->longitudPista = 60;
        threadInfo->vuelta = 1;
        threadInfo->numVueltas = 7;
        pthread_create(&threads[i], NULL, &funcionCaballo, threadInfo); // Se crea el hilo. Primer parametro son los hilos creados anteriormente, segundo parametro NULL, tercer parametro es la funcion a ejecutar
                                                                        // Cuarto parametro es el struct de tipo puntero con los atributos para cada hilo
    }
    for (int i = 0; i < numCaballos; i++) // Ciclo for para comprobar el termino de la ejecucion de cada hilo antes de realizar otra tarea.
    {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&mutex); // Destruye el MUTEX al final del programa para liberar memoria.
}