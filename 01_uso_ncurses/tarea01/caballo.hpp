/* Declaración de funciones */

#ifndef CABALLO_HPP
#define CABALLO_HPP

struct Caballo // Estructura que almacena la posición y velocidad de cada caballo
{
    int posicion;
    int velocidad;
};

// Función que define, de forma aleatoria, el movimiento de los caballos durante la carrera
void avanzarCaballo(Caballo &);
// Función que muestra por pantalla al ganador, una vez finalizada la carrera
void mostrarGanador(Caballo[], int, int);

#endif