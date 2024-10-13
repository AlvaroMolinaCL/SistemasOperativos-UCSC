# Carrera de Caballos

## Descripción

A través de este programa, usted podrá simular a través de su terminal, una carrera de caballos como si estuviera en un hipódromo. Podrá elegir la cantidad de caballos que competirán (mínimo 2 y máximo 20) y el tamaño de la pista que tendrá el hipódromo (mínimo 20 y máximo 100).

## Requisitos del sistema

* Sistema operativo: GNU/Linux.
* Terminal de comandos:
  * GNU/Linux: Bash.
* Compilador gcc/g++.

## Instrucciones de compilación

Si va a ejecutar por primera vez el programa, debe compilarlo. Para lo anterior, debe ejecutar su terminal y posicionarla en el mismo directorio donde se encuentra el programa. Luego, debe escribir lo siguiente:

`g++ caballo.cpp hipodromo.cpp main.cpp -o main -lncurses`

Si al compilar, indica error al no encontrar la biblióteca ncurses, se debe instalar con el siguiente comando (y luego volver a intentar con el anterior):

`sudo apt install libncurses5-dev libncursesw5-dev`

Finalmente, para ejecutar el programa, debe escribir lo siguiente:

`main`

## Consideraciones generales

* El avance y velocidad de los caballos durante las carreras es definido automática y aleatoriamente al inicio de cada carrera.
* Debido a limitaciones por el tamaño de pantalla y memoria, no se pueden simular carreras con más de 20 caballos y las pistas del hipódromo pueden tener solo un máximo de 100 metros.