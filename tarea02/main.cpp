/* Tarea 2 - Sistemas Operativos (IN1077C) - UCSC */

/**
 * @file main.cpp
 * @author Álvaro Molina Jara (amolinaj@ing.ucsc.cl)
 * @brief Compilar con g++ -o main main.cpp hipodromo.cpp caballo.cpp -lncurses -lpthread
 * @details Implementación de juego que simula carrera de caballos usando programación modular, con manejo de pantalla mediante ncurses.h y
 *          uso de hebras de control mediante pthread.h.
 * @version 2.0
 * @date 2024-05-20
 **/

#include <iostream>      // exit(), srand()
#include <ncurses.h>     // Manejo por pantalla del programa
#include <pthread.h>     // Uso de hebras de control
#include "hipodromo.hpp" // Aquí se controla todo el proceso de la carrera en el hipódromo (aquí también se incluye caballo.hpp)

using namespace std;

int main(int argc, char const *argv[])
{
    srand(time(0)); // Semilla para generar números aleatorios

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
            init_pair(1, COLOR_WHITE, COLOR_GREEN); // Se definen colores de letra y fondo para el título (líneas 38-40)
            attron(A_BOLD);
            attron(COLOR_PAIR(1));
            mvprintw(9, 67, "** CARRERA DE CABALLOS v2.0 **");
            attroff(COLOR_PAIR(1));
            attroff(A_BOLD);
            mvprintw(12, 20, "A través de este programa, usted podrá simular a través de su terminal, una carrera de caballos como si estuviera en un hipódromo.");
            mvprintw(13, 20, "Podrá elegir la cantidad de caballos que competirán (mínimo 2 y máximo 7), el tamaño de la pista (30, 40, 50, ó 60 metros), y la");
            mvprintw(14, 20, "cantidad de vueltas que darán los caballos en la pista (mínimo 1 y máximo 4).");
            mvprintw(15, 20, "Mayor información, instrucciones y consideraciones generales del programa las podrá encontrar en el archivo README.md, ubicado en");
            mvprintw(16, 20, "el mismo directorio donde está siendo ejecutado.");
            mvprintw(18, 20, "Para continuar, escriba el número de una de las opciones indicadas a continuación:");
            mvprintw(20, 20, "1. Iniciar carrera");
            mvprintw(21, 20, "2. Salir del programa");
            mvprintw(23, 20, ">> ");
            refresh();
            aux = scanw("%d", &opMenu);
        } while (aux == FALSE || aux == ERR || opMenu < 1 || opMenu > 2);
        if (opMenu == 1)
        {
            prepararCarrera();
        }
        break;
    } while (opMenu != 2); // Se indica el número de la opción para salir del programa desde el menú principal

    mvprintw(25, 20, "Ha finalizado la ejecución del programa, presione cualquier tecla para salir...");
    refresh();
    getch();
    endwin();                      // Se cierra ncurses y finaliza el programa
    pthread_mutex_destroy(&mutex); // Se destruye el MUTEX para liberar memoria

    exit(0);
}
