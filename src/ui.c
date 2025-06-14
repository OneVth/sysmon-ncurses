#include <ncurses.h>
#include "ui.h"

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
    // TODO
}

void CloseUI(void)
{
    endwin();
}