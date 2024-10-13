/*
	Para compilar este programa use el siguiente comando en una terminal
	en el mismo directorio donde se encuentra el código fuente:
	gcc -o menu_ejemplo menu_ejemplo.c -lncurses

	Si al compilar marca un error de que no encuentra la biblioteca ncurses
	esta se debe instalar utilizando el siguiente comando:
	sudo apt install libncurses5-dev libncursesw5-dev
*/

#include <stdlib.h>
#include <ncurses.h>

int main(void)
{
	int op, aux;

	initscr();
	// curs_set(0);

	do
	{
		do
		{
			erase();
			refresh();
			attron(A_BOLD | A_UNDERLINE);
			mvprintw(3, 33, "MENU");
			attroff(A_BOLD | A_UNDERLINE);
			mvprintw(5, 25, "1. Opción 1");
			mvprintw(6, 25, "2. Opción 2");
			mvprintw(7, 25, "3. Opción 3");
			mvprintw(8, 25, "4. Opción 4");
			mvprintw(9, 25, "5. Salir");
			mvprintw(11, 25, "Ingrese su opción: ");
			refresh();
			aux = scanw("%d", &op);
		} while (aux == FALSE || aux == ERR || op < 1 || op > 5);
		switch (op)
		{
		case 1:
			mvprintw(13, 25, "La opción elegida fue la 1");
			break;
		case 2:
			mvprintw(13, 25, "La opción elegida fue la 2");
			break;
		case 3:
			mvprintw(13, 25, "La opción elegida fue la 3");
			break;
		case 4:
			mvprintw(13, 25, "La opción elegida fue la 4");
			break;
		case 5:
			mvprintw(13, 25, "La opción elegida fue la Salir");
			break;
		}
		getch();
	} while (op != 5);
	
	endwin();
	exit(0);
}