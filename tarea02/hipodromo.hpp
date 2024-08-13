/* Declaración de funciones */

#ifndef HIPODROMO_HPP
#define HIPODROMO_HPP

#include <ncurses.h>   // Manejo por pantalla del programa
#include <pthread.h>   // Uso de hebras de control
#include <cstdlib>     // rand()
#include <ctime>       // time()
#include <vector>      // vector
#include "caballo.hpp" // Aquí se controla el avance de los caballos y la declaración del caballo ganador en cada carrera

using namespace std;

// Función que recoge información necesaria para iniciar la carrera de caballos
void prepararCarrera();
// Función que inicia la carrera de caballos, una vez recogida la información desde prepararCarrera()
void iniciarCarrera();
// Función que demarca la pista del hipódromo, de acuerdo a la cantidad de metros que se van a correr
void demarcarPista(int);

#endif