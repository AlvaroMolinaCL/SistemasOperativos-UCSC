#include "hipodromo.hpp" // Aquí se controla todo el proceso de la carrera en el hipódromo (aquí también se incluye caballo.hpp)

int numCaballos;
int tamPista;
int numVueltas;
vector<Caballo> caballos; // Vector que almacena la información de todos los caballos que van a competir
bool carreraTerminada = false;
int caballoGanador = -1;
pthread_mutex_t mutex; // Declaración de MUTEX

void prepararCarrera()
{
    initscr();   // Aquí comienza el manejo por pantalla desde ncurses
    cbreak();    // Se permite mostrar la entrada de texto por pantalla
    curs_set(0); // Se oculta el cursor de texto, para que no se vea al escribir

    int aux; // Variable auxiliar para controlar el ingreso de datos erróneos por pantalla

    do
    {
        erase();
        refresh();
        mvprintw(12, 20, "Para poder iniciar la carrera, favor ingrese la información solicitada.");
        mvprintw(14, 23, "Número de caballos (mínimo 2 y máximo 7): "); // Se solicita ingresar el número de caballos que van a competir
        refresh();
        aux = scanw("%d", &numCaballos);
    } while (aux == FALSE || aux == ERR || numCaballos < 2 || numCaballos > 7);

    do
    {
        erase();
        refresh();
        mvprintw(12, 20, "Para poder iniciar la carrera, favor ingrese la información solicitada.");
        mvprintw(14, 23, "Tamaño de la pista (ingresar solo el número: 30, 40, 50, ó 60): "); // Se solicita ingresar el tamaño que tendrá la pista para cada uno de los caballos
        refresh();
        aux = scanw("%d", &tamPista);
    } while (aux == FALSE || aux == ERR || (tamPista != 30 && tamPista != 40 && tamPista != 50 && tamPista != 60));

    do
    {
        erase();
        refresh();
        mvprintw(12, 20, "Para poder iniciar la carrera, favor ingrese la información solicitada.");
        mvprintw(14, 23, "Cantidad de vueltas (mínimo 1 y máximo 4): "); // Se solicita ingresar la cantidad de vueltas que darán cada uno de los caballos
        refresh();
        aux = scanw("%d", &numVueltas);
    } while (aux == FALSE || aux == ERR || numVueltas < 1 || numVueltas > 4);

    erase();
    refresh();
    if (numVueltas == 1)
    {
        mvprintw(12, 20, "En la carrera competirán %d caballos, la pista del hipódromo será de %d metros,", numCaballos, tamPista);
        mvprintw(13, 20, "y se correrá %d vuelta.", numVueltas);
        mvprintw(14, 20, "Ya está todo listo para empezar. Presione cualquier tecla para dar la largada...");
    }
    else
    {
        mvprintw(12, 20, "En la carrera competirán %d caballos, la pista del hipódromo será de %d metros,", numCaballos, tamPista);
        mvprintw(13, 20, "y se correrán %d vueltas.", numVueltas);
        mvprintw(14, 20, "Ya está todo listo para empezar. Presione cualquier tecla para dar la largada...");
    }
    getch();

    refresh();
    mvprintw(16, 20, "2"); // Cuenta regresiva para iniciar la carrera

    refresh();
    mvprintw(16, 20, "1");
    napms(1000);

    refresh();
    mvprintw(16, 20, "¡Comienza la carrera!");
    napms(1000);

    caballos.resize(numCaballos);   // Se reasigna el tamaño del vector caballos, de acuerdo a la cantidad de caballos que van a competir
    pthread_t threads[numCaballos]; // Se crean n cantidad de hebras para los n caballos que van a competir (n = numCaballos)

    for (int i = 0; i < numCaballos; i++)
    {
        caballos[i] = {i + 1, 0, 0, 0};                                     // Se inicializa la información de cada caballo (id, posicion, vueltas, metrosTotales), antes de iniciar la carrera
        pthread_create(&threads[i], nullptr, avanzarCaballo, &caballos[i]); // Se crean las hebras
    }

    iniciarCarrera(); // Se llama a la función iniciarCarrera para dar por iniciada la carrera

    for (int i = 0; i < numCaballos; i++) // Ciclo para comprobar el termino de la ejecución de cada hilo antes de realizar otra tarea
    {
        pthread_join(threads[i], nullptr);
    }

    int numero_carrera = rand() % 1000 + 1;                               // Se asigna un número aleatorio (entre 1 y 1000) para el ID de la carrera
    mostrarGanador(numero_carrera, tamPista, numVueltas, caballoGanador); // Cuando ha finalizado la carrera (dentro de iniciarCarrera), se llama a
                                                                          // mostrarGanador para mostrar por pantalla la info. de la carrera y el ganador
}

void iniciarCarrera()
{
    initscr();   // Aquí comienza el manejo por pantalla desde ncurses
    cbreak();    // Se permite mostrar la entrada de texto por pantalla
    curs_set(0); // Se oculta el cursor de texto, para que no se vea al escribir

    while (!carreraTerminada) // Ciclo que se ejecuta mientras la carrera esté en desarrollo
    {
        pthread_mutex_lock(&mutex); // Se bloquea sección crítica (líneas 106-142) para que solo sea accedida por 1 hebra a la vez
        clear();
        int totalVueltas = 0; // Variable para la sumatoria de vueltas que han dado todos los caballos
        int totalMetros = 0;  // Variable para la sumatoria de metros que han corrido todos los caballos

        demarcarPista(tamPista);              // Se demarca la pista con la cantidad de metros que se van a correr
        for (int i = 0; i < numCaballos; i++) // Ciclo que va actualizando la posición de los caballos durante la carrera
        {
            mvprintw(i + 9, 20, "Caballo %d: ", caballos[i].id); // Se imprime por pantalla la posición del caballo
            for (int j = 0; j < caballos[i].posicion; j++)       // Ciclo que imprime el avance de los caballos, hasta que uno llegue a la meta
            {
                attron(A_BOLD);
                printw("|");
            }
            printw(" -->>\n");
            attroff(A_BOLD);
            if (caballos[i].vueltas == 1)
            {
                mvprintw(i + 9, 102, " %d vuelta, %d metros", caballos[i].vueltas, caballos[i].metrosTotales);
            }
            else
            {
                mvprintw(i + 9, 102, " %d vueltas, %d metros", caballos[i].vueltas, caballos[i].metrosTotales);
            }
            totalVueltas += caballos[i].vueltas;      // Se van sumando las vueltas que han dado todos los caballos
            totalMetros += caballos[i].metrosTotales; // Se van sumando los metros corridos por todos los caballos
        }

        mvprintw(numCaballos + 10, 20, "Total: "); // Debajo de la pista, se muestra la suma de vueltas y metros corridos por todos los caballos
        if (totalVueltas == 1)
        {
            mvprintw(numCaballos + 10, 103, "%d vuelta, %d metros", totalVueltas, totalMetros);
        }
        else
        {
            mvprintw(numCaballos + 10, 103, "%d vueltas, %d metros", totalVueltas, totalMetros);
        }
        refresh();
        pthread_mutex_unlock(&mutex); // Se desbloquea sección crítica
        usleep(100000);
    }
}

void demarcarPista(int tamPista)
{
    initscr();   // Aquí comienza el manejo por pantalla desde ncurses
    cbreak();    // Se permite mostrar la entrada de texto por pantalla
    curs_set(0); // Se oculta el cursor de texto, para que no se vea al escribir

    if (tamPista == 30)
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
    else if (tamPista == 40)
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
    else if (tamPista == 50)
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
    else if (tamPista == 60)
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
}