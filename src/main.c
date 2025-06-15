#include <stdio.h>
#include <ncurses.h>
#include "ui.h"

void ui_test(void)
{
	InitUI();

	DrawMemoryUsage();
	DrawCpuUsage();

	getch();
	CloseUI();
}

int main(void)
{
	ui_test();
	return 0;
}
