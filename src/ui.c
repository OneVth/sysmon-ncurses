#include <ncurses.h>
#include "ui.h"
#include "memory.h"

void InitUI(void)
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    box(stdscr, 0, 0);
    refresh();
}

void DrawMemoryUsage(void)
{
    int width = 20;

	int total = GetTotMem() / 1024;		// convert kB to MB
	int avail = GetAvailMem() / 1024; 	// convert kB to MB
	double usage = GetMemUsage();		// return % value

	mvprintw(1, 2, "Memory Usage");

	int filled = (int)(width * usage / 100);
	mvprintw(2, 2, "[");
	for (int i = 0; i < width; i++)
	{
		if (i < filled)
			addch('=');
		else
			addch(' ');
	}
	printw("]");
	printw(" %.1f%%", usage);

	mvprintw(4, 2, "%d MB / %d MB", total - avail, total);
}

void CloseUI(void)
{
    endwin();
}