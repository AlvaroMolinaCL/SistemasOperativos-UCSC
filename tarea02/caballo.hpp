/* Declaración de funciones */

#ifndef CABALLO_HPP
#define CABALLO_HPP

#include <cstdlib>   // rand()
#include <ncurses.h> // Manejo por pantalla del programa
#include <pthread.h> // Uso de hebras de control
#include <unistd.h>  // usleep()
#include <vector>    // vector

using namespace std;

struct Caballo // Estructura que almacena la posición y cantidad de vueltas de cada caballo, además de los metros totales para la sumatoria.
{
    int id;
    int posicion;
    int vueltas;
    int metrosTotales;
};

// Variables que almacenan la información necesaria para la carrera
extern int numCaballos;
extern int tamPista;
extern int numVueltas;
extern vector<Caballo> caballos; // Vector que almacena la información de todos los caballos que van a competir
extern bool carreraTerminada;
extern int caballoGanador;
extern pthread_mutex_t mutex; // Declaración de MUTEX

// Función que controla el avance de los caballos (aleatorio entre 0 y 1 posición), haciendo uso de hebras de control
void *avanzarCaballo(void *);
// Función que muestra por pantalla información de la carrera junto con  el caballo ganador, una vez finalizada la misma
void mostrarGanador(int, int, int, int);

#endif