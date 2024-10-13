# Carrera de Caballos v2.0

## Descripción

A través de este programa, usted podrá simular a través de su terminal, una carrera de caballos como si estuviera en un hipódromo. Podrá elegir la cantidad de caballos que competirán (mínimo 2 y máximo 7), el tamaño de la pista que tendrá el hipódromo (30, 40, 50, ó 60 metros), y la cantidad de vueltas que darán los caballos en la pista (mínimo 1 y máximo 4).

## Requisitos del sistema

* Sistema operativo: GNU/Linux.
* Terminal de comandos:
  * GNU/Linux: Bash.
* Compilador gcc/g++.

## Instrucciones de compilación

Si va a ejecutar por primera vez el programa, debe compilarlo. Para lo anterior, debe ejecutar su terminal y posicionarla en el mismo directorio donde se encuentra el programa. Luego, debe escribir lo siguiente:

`g++ -o main main.cpp hipodromo.cpp caballo.cpp -lncurses -lpthread`

Si al compilar, indica error al no encontrar las bibliotecas ncurses y/o pthread, se deben instalar con el siguiente comando (y luego volver a intentar con el anterior):

`sudo apt install libncurses5-dev libncursesw5-dev libpthread-stubs0-dev`

Finalmente, para ejecutar el programa, debe escribir lo siguiente:

`main`

## Consideraciones generales

* El avance de los caballos durante el desarrollo de las carreras, es definido de forma aleatoria.
* Debido a limitaciones por el tamaño de pantalla y memoria, además de la necesidad del uso de hebras de control en funciones críticas del programa (como aquellas que controlan el avance de los caballos o que van imprimiendo por pantalla el desarrollo de la carrera), no se pueden simular carreras con más de 7 caballos y las pistas del hipódromo pueden tener solo un máximo de 60 metros.