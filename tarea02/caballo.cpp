#include "caballo.hpp" // Aquí se controla el avance de los caballos y la declaración del caballo ganador en cada carrera

void *avanzarCaballo(void *args)
{
    Caballo *caballo = (Caballo *)args;

    while (!carreraTerminada) // Ciclo que se ejecuta mientras la carrera esté en desarrollo
    {
        usleep(100000);
        pthread_mutex_lock(&mutex); // Se bloquea sección crítica (líneas 11-27) para que solo sea accedida por 1 hebra a la vez
        if (caballo->vueltas < numVueltas)
        {
            int avanceCaballo = rand() % 2;          // Se suma un número aleatorio entre 0 y 1 a la posición de cada caballo, para simular su avance
            caballo->posicion += avanceCaballo;      // Se suma a la posición, el número aleatorio entregado por avanceCaballo
            caballo->metrosTotales += avanceCaballo; // Se suma a los metros totales, el número aleatorio por avanceCaballo
            if (caballo->posicion >= tamPista)       // Condicional para contabilizar las vueltas durante la carrera
            {
                caballo->posicion = 0; // Una vez que el caballo completa una vuelta, este vuelve a aparecer al principio de la pista para
                                       // iniciar una nueva vuelta
                caballo->vueltas++;    // Se suma 1 vuelta
            }
            if (caballo->vueltas >= numVueltas && caballoGanador == -1) // Condicional que se ejecuta cuando se han corrido todas las vueltas en la carrera
            {
                caballoGanador = caballo->id; // Se asigna como ganador al primer caballo que haya completado todas las vueltas de la carrera
                carreraTerminada = true;      // Se da por finalizada la carrera, asignando true a carreraTerminada para salir del ciclo while
            }
        }
        pthread_mutex_unlock(&mutex); // Se desbloquea sección crítica
    }
    return nullptr;
}

void mostrarGanador(int idCarrera, int tamPista, int numVueltas, int caballoGanador)
{
    mvprintw(numCaballos + 12, 20, "ID de la carrera:     %d", idCarrera);       // Se muestra el ID de la carrera (número generado aleatoriamente entre 1 y 1000)
    mvprintw(numCaballos + 13, 20, "Tamaño de la pista:   %d metros", tamPista); // Se muestra el tamaño de la pista (definido para la carrera por el usuario)
    mvprintw(numCaballos + 14, 20, "Cantidad de vueltas:  %d", numVueltas);      // Se muestra la cantidad de vueltas (definido para la carrera por el usuario)
    attron(A_BOLD);
    mvprintw(numCaballos + 16, 20, "¡El Caballo %d es el ganador de la carrera!", caballoGanador); // Se muestra por pantalla al caballo ganador
    attroff(A_BOLD);
    mvprintw(25, 20, "Ha finalizado la ejecución del programa, presione cualquier tecla para salir...");
    refresh();
}
