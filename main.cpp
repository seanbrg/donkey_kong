#include <Windows.h>
#include <iostream>
#include <conio.h> // for keyboard control

#include "menu.h"

int main()
{	
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	MoveWindow(console, r.left, r.top, 80, 25, TRUE); // 80 width, 25 height

	Menu menu;
	menu.display();
}