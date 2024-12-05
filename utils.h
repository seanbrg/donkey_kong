#pragma once
#include <iostream>
#include <conio.h> // for keyboard control
#include <Windows.h> // for sleep

void gotoxy(int x, int y);

void ShowConsoleCursor(bool showFlag);

enum class eKeys { LEFT = 'a', RIGHT = 's', UP = 'w', DOWN = 'z', ESC = 27 };

class Point {
public:
	int x, y;
	Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
};

struct Direction { int x, y; };