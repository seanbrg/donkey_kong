#include "utils.h"
#include <Windows.h>

using namespace colors;

void gotoxy(int x, int y) {
    std::cout.flush();
    COORD coord; // Create a COORD structure 
    coord.X = x; // Set the X coordinate 
    coord.Y = y; // Set the Y coordinate 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // Move the cursor 
}

void ShowConsoleCursor(bool showFlag) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void changeColor(char type)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    unsigned short color;
    switch (type) {
	case ch_mario:
		color = BRIGHT_YELLOW;
		break;
	case ch_dead_mario:
		color = BRIGHT_YELLOW;
		break;
	case ch_floor_flat:
		color = BRIGHT_RED;
		break;
	case ch_floor_left:
		color = BRIGHT_RED;
		break;
	case ch_floor_right:
		color = BRIGHT_RED;
		break;
	case ch_ladder:
		color = BRIGHT_BLUE;
		break;
	case ch_pauline:
		color = PINK;
		break;
	case ch_explosion:
		color = ORANGE;
		break;
	case ch_dk:
		color = ORANGE;
		break;
	case ch_ghost:
		color = GREEN;
		break;
	case 'e': // easy (for the menu)
		color = GREEN;
		break;
	case 'h': // hard (for the menu)
		color = RED;
		break;
	default:
		color = WHITE;
	}
		SetConsoleTextAttribute(hConsole, color);
}
