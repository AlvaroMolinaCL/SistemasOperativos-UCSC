#include <cstdlib>     // rand()
#include <ncurses.h>   // Manejo por pantalla del programa
#include "caballo.hpp" // Aquí se define el avance de los caballos y cómo mostrar al ganador

void avanzarCaballo(Caballo &caballo)
{
    caballo.posicion += rand() % caballo.velocidad + 1; // Se suma un número entre 1 y la velocidad entre cada posición del caballo en la pista
}

void mostrarGanador(Caballo pistaHipodromo[], int numCaballos, int tamPista)
{
    initscr();   // Aquí comienza el manejo por pantalla desde ncurses
    cbreak();    // Se permite mostrar la entrada de texto por pantalla
    curs_set(0); // Se oculta el cursor de texto, para que no se vea al escribir

    for (int i = 0; i < numCaballos; i++) // Ciclo que comprueba la posición de cada caballo en la pista
    {
        if (pistaHipodromo[i].posicion >= tamPista) // Se verifica si algún caballo ha llegado a la meta
        {
            refresh();
            attron(A_BOLD);
            mvprintw(numCaballos + 10, 20, "¡El Caballo %d es el ganador de la carrera!", i + 1); // Se muestra por pantalla al caballo ganador
            attroff(A_BOLD);
            mvprintw(numCaballos + 12, 20, "Ha finalizado la ejecución del programa, presione cualquier tecla para salir...");
            refresh();
            getch();
            endwin();
            exit(0);
        }
    }
}