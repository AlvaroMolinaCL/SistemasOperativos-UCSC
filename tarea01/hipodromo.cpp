#include <iostream>
#include <ncurses.h>     // Manejo por pantalla del programa
#include "caballo.hpp"   // Aquí se define el avance de los caballos y cómo mostrar al ganador
#include "hipodromo.hpp" // Aquí se controla todo el proceso de la carrera en el hipódromo

using namespace std;

void iniciarCarrera(int numCaballos, int tamPista)
{
    initscr();   // Aquí comienza el manejo por pantalla desde ncurses
    cbreak();    // Se permite mostrar la entrada de texto por pantalla
    curs_set(0); // Se oculta el cursor de texto, para que no se vea al escribir

    Caballo pistaHipodromo[numCaballos];  // Se define vector para cada una de las pistas donde correrán los caballos
    for (int i = 0; i < numCaballos; i++) // Se inicializan todas las posiciones de los caballos en 0, y se les asigna aleatoriamente una velocidad entre 1 y 6
    {
        pistaHipodromo[i].posicion = 0;
        pistaHipodromo[i].velocidad = rand() % 6 + 1;
    }

    while (true)
    {
        erase();
        demarcarPista(tamPista);              // Se demarca la pista con la cantidad de metros que se van a correr
        for (int i = 0; i < numCaballos; i++) // Ciclo que va actualizando, cada 1 segundo, la posición de los caballos durante la carrera
        {
            avanzarCaballo(pistaHipodromo[i]);
            mvprintw(i + 9, 20, "Caballo %d:\t", i + 1);         // Se imprime por pantalla la posición del caballo
            for (int j = 0; j < pistaHipodromo[i].posicion; j++) // Ciclo que imprime el avance de los caballos, hasta que uno llegue a la meta
            {
                attron(A_BOLD);
                printw("|");
            }
            printw(" -->>\n");
            attroff(A_BOLD);
        }

        refresh();
        napms(1000);

        mostrarGanador(pistaHipodromo, numCaballos, tamPista);
    }
}

void demarcarPista(int tamPista)
{
    initscr();   // Aquí comienza el manejo por pantalla desde ncurses
    cbreak();    // Se permite mostrar la entrada de texto por pantalla
    curs_set(0); // Se oculta el cursor de texto, para que no se vea al escribir

    if (tamPista == 20)
    {
        mvprintw(7, 32, "000");
        mvprintw(7, 38, "|");
        mvprintw(7, 42, "010");
        mvprintw(7, 48, "|");
        mvprintw(7, 52, "020");
        mvprintw(7, 58, "(m)");
    }
    else if (tamPista > 20 && tamPista <= 30)
    {
        mvprintw(7, 32, "000");
        mvprintw(7, 38, "|");
        mvprintw(7, 42, "010");
        mvprintw(7, 48, "|");
        mvprintw(7, 52, "020");
        mvprintw(7, 58, "|");
        mvprintw(7, 62, "030");
        mvprintw(7, 68, "(m)");
    }
    else if (tamPista > 30 && tamPista <= 40)
    {
        mvprintw(7, 32, "000");
        mvprintw(7, 38, "|");
        mvprintw(7, 42, "010");
        mvprintw(7, 48, "|");
        mvprintw(7, 52, "020");
        mvprintw(7, 58, "|");
        mvprintw(7, 62, "030");
        mvprintw(7, 68, "|");
        mvprintw(7, 72, "040");
        mvprintw(7, 78, "(m)");
    }
    else if (tamPista > 40 && tamPista <= 50)
    {
        mvprintw(7, 32, "000");
        mvprintw(7, 38, "|");
        mvprintw(7, 42, "010");
        mvprintw(7, 48, "|");
        mvprintw(7, 52, "020");
        mvprintw(7, 58, "|");
        mvprintw(7, 62, "030");
        mvprintw(7, 68, "|");
        mvprintw(7, 72, "040");
        mvprintw(7, 78, "|");
        mvprintw(7, 82, "050");
        mvprintw(7, 88, "(m)");
    }
    else if (tamPista > 50 && tamPista <= 60)
    {
        mvprintw(7, 32, "000");
        mvprintw(7, 38, "|");
        mvprintw(7, 42, "010");
        mvprintw(7, 48, "|");
        mvprintw(7, 52, "020");
        mvprintw(7, 58, "|");
        mvprintw(7, 62, "030");
        mvprintw(7, 68, "|");
        mvprintw(7, 72, "040");
        mvprintw(7, 78, "|");
        mvprintw(7, 82, "050");
        mvprintw(7, 88, "|");
        mvprintw(7, 92, "060");
        mvprintw(7, 98, "(m)");
    }
    else if (tamPista > 60 && tamPista <= 70)
    {
        mvprintw(7, 32, "000");
        mvprintw(7, 38, "|");
        mvprintw(7, 42, "010");
        mvprintw(7, 48, "|");
        mvprintw(7, 52, "020");
        mvprintw(7, 58, "|");
        mvprintw(7, 62, "030");
        mvprintw(7, 68, "|");
        mvprintw(7, 72, "040");
        mvprintw(7, 78, "|");
        mvprintw(7, 82, "050");
        mvprintw(7, 88, "|");
        mvprintw(7, 92, "060");
        mvprintw(7, 98, "|");
        mvprintw(7, 102, "070");
        mvprintw(7, 108, "(m)");
    }
    else if (tamPista > 70 && tamPista <= 80)
    {
        mvprintw(7, 32, "000");
        mvprintw(7, 38, "|");
        mvprintw(7, 42, "010");
        mvprintw(7, 48, "|");
        mvprintw(7, 52, "020");
        mvprintw(7, 58, "|");
        mvprintw(7, 62, "030");
        mvprintw(7, 68, "|");
        mvprintw(7, 72, "040");
        mvprintw(7, 78, "|");
        mvprintw(7, 82, "050");
        mvprintw(7, 88, "|");
        mvprintw(7, 92, "060");
        mvprintw(7, 98, "|");
        mvprintw(7, 102, "070");
        mvprintw(7, 108, "|");
        mvprintw(7, 112, "080");
        mvprintw(7, 118, "(m)");
    }
    else if (tamPista > 80 && tamPista <= 90)
    {
        mvprintw(7, 32, "000");
        mvprintw(7, 38, "|");
        mvprintw(7, 42, "010");
        mvprintw(7, 48, "|");
        mvprintw(7, 52, "020");
        mvprintw(7, 58, "|");
        mvprintw(7, 62, "030");
        mvprintw(7, 68, "|");
        mvprintw(7, 72, "040");
        mvprintw(7, 78, "|");
        mvprintw(7, 82, "050");
        mvprintw(7, 88, "|");
        mvprintw(7, 92, "060");
        mvprintw(7, 98, "|");
        mvprintw(7, 102, "070");
        mvprintw(7, 108, "|");
        mvprintw(7, 112, "080");
        mvprintw(7, 118, "|");
        mvprintw(7, 122, "090");
        mvprintw(7, 128, "(m)");
    }
    else if (tamPista > 90 && tamPista <= 100)
    {
        mvprintw(7, 32, "000");
        mvprintw(7, 38, "|");
        mvprintw(7, 42, "010");
        mvprintw(7, 48, "|");
        mvprintw(7, 52, "020");
        mvprintw(7, 58, "|");
        mvprintw(7, 62, "030");
        mvprintw(7, 68, "|");
        mvprintw(7, 72, "040");
        mvprintw(7, 78, "|");
        mvprintw(7, 82, "050");
        mvprintw(7, 88, "|");
        mvprintw(7, 92, "060");
        mvprintw(7, 98, "|");
        mvprintw(7, 102, "070");
        mvprintw(7, 108, "|");
        mvprintw(7, 112, "080");
        mvprintw(7, 118, "|");
        mvprintw(7, 122, "090");
        mvprintw(7, 128, "|");
        mvprintw(7, 132, "100");
        mvprintw(7, 138, "(m)");
    }
}

void prepararCarrera()
{
    int numCaballos, tamPista, aux; // Variables para almacenar el número de caballos que competirán, el tamaño de la pista, y auxiliar para
                                    // controlar el ingreso de datos erróneos por pantalla.

    do
    {
        erase();
        refresh();
        mvprintw(12, 20, "Para poder iniciar la carrera, favor ingrese la información solicitada.");
        mvprintw(14, 23, "Número de caballos: "); // Se solicita ingresar el número de caballos que van a competir
        refresh();
        aux = scanw("%d", &numCaballos);
    } while (aux == FALSE || aux == ERR || numCaballos < 2 || numCaballos > 20);

    do
    {
        erase();
        refresh();
        mvprintw(12, 20, "Para poder iniciar la carrera, favor ingrese la información solicitada.");
        mvprintw(14, 23, "Tamaño de la pista: "); // Se solicita ingresar el tamaño que tendrá la pista para cada uno de los caballos
        refresh();
        aux = scanw("%d", &tamPista);
    } while (aux == FALSE || aux == ERR || tamPista < 20 || tamPista > 100);

    erase();
    refresh();
    mvprintw(12, 20, "En la carrera participarán %d caballos y la pista del hipódromo será de %d metros.", numCaballos, tamPista);
    mvprintw(13, 20, "Ya está todo listo para empezar. Presione cualquier tecla para dar la largada...");
    getch();

    refresh();
    mvprintw(15, 20, "2"); // Cuenta regresiva para iniciar la carrera

    refresh();
    mvprintw(15, 20, "1");
    napms(1000);

    refresh();
    mvprintw(15, 20, "¡Comienza la carrera!");
    napms(1000);

    iniciarCarrera(numCaballos, tamPista);
}