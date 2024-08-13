/* Tarea 1 - Sistemas Operativos (IN1077C) - UCSC */

/**
 * @file main.cpp
 * @author Álvaro Molina Jara (amolinaj@ing.ucsc.cl)
 * @brief Compilar con g++ caballo.cpp hipodromo.cpp main.cpp -o main -lncurses
 * @details Implementación de juego que simula carrera de caballos usando programación modular y con manejo de pantalla mediante ncurses.h.
 * @version 0.1
 * @date 2024-04-06
 **/

#include <iostream>      // exit(), srand()
#include <ncurses.h>     // Manejo por pantalla del programa
#include "hipodromo.hpp" // Aquí se controla todo el proceso de la carrera en el hipódromo (aquí también se incluye caballo.hpp)

using namespace std;

int main(int argc, char const *argv[])
{
    srand(time(NULL)); // Semilla para generar números aleatorios (necesaria para controlar el avance de los caballos)

    int opMenu, aux; // Variables para controlar el menú principal del programa
    initscr();       // Aquí comienza el manejo por pantalla desde ncurses
    cbreak();        // Se permite mostrar la entrada de texto por pantalla
    curs_set(0);     // Se oculta el cursor de texto, para que no se vea al escribir

    do // Menú principal del programa
    {
        do // Ciclo que mantiene el menú en pantalla mientras no se seleccione una opción correcta
        {
            erase();
            refresh();
            start_color();
            init_pair(1, COLOR_WHITE, COLOR_GREEN); // Se definen colores de letra y fondo para el título (línea 38)
            attron(A_BOLD);
            attron(COLOR_PAIR(1));
            mvprintw(9, 72, "** CARRERA DE CABALLOS **");
            attroff(COLOR_PAIR(1));
            attroff(A_BOLD);
            mvprintw(12, 20, "A través de este programa, usted podrá simular a través de su terminal, una carrera de caballos como si estuviera en un hipódromo.");
            mvprintw(13, 20, "Podrá elegir la cantidad de caballos (mínimo 2 y máximo 20) y el tamaño de la pista (mínimo 20 y máximo 100).");
            mvprintw(14, 20, "Mayor información, instrucciones y consideraciones generales del programa las podrá encontrar en el archivo README.md, ubicado");
            mvprintw(15, 20, "en el mismo directorio donde está siendo ejecutado.");
            mvprintw(17, 20, "Para continuar, escriba el número de una de las opciones indicadas a continuación:");
            mvprintw(19, 20, "1. Iniciar carrera");
            mvprintw(20, 20, "2. Salir del programa");
            mvprintw(22, 20, ">> ");
            refresh();
            aux = scanw("%d", &opMenu);
        } while (aux == FALSE || aux == ERR || opMenu < 1 || opMenu > 2);
        if (opMenu == 1)
        {
            prepararCarrera();
        }
    } while (opMenu != 2); // Se indica el número de la opción para salir del programa desde el menú principal

    mvprintw(24, 20, "Ha finalizado la ejecución del programa, presione cualquier tecla para salir...");
    refresh();
    getch();
    endwin(); // Se cierra ncurses y finaliza el programa
    exit(0);
}
