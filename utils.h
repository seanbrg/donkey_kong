#pragma once
#include <iostream>
#include <conio.h> // for keyboard control
#include <Windows.h> // for sleep

void gotoxy(int x, int y);

void ShowConsoleCursor(bool showFlag);

void changeColor(char type = ' ');

namespace keys {
	enum Key {
		LEFT = 'a',
		RIGHT = 'd',
		UP = 'w',
		DOWN = 'x',
		STAY = 's',
		ESC = 27
	};
};

namespace colors {
	enum Color {
		RED = FOREGROUND_RED,
		BRIGHT_RED = FOREGROUND_RED | FOREGROUND_INTENSITY,
		ORANGE = FOREGROUND_RED | FOREGROUND_GREEN,
		BRIGHT_YELLOW = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
		BLUE = FOREGROUND_BLUE,
		BRIGHT_BLUE = FOREGROUND_BLUE | FOREGROUND_INTENSITY,
		PINK = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
		GREEN = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
		WHITE = (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
	};
};

static constexpr int MIN_X = 0;
static constexpr int MIN_Y = 0;
static constexpr int MAX_X = 79;
static constexpr int MAX_Y = 25;
static const int explosion_range = 2;

static const char ch_border = 'Q';
static const char ch_ladder = 'H';
static const char ch_floor_flat = '=';
static const char ch_floor_left = '<';
static const char ch_floor_right = '>';
static const char ch_pauline = '$';
static const char ch_dk = '&';
static const char ch_mario = '@';
static const char ch_barrel = 'O';
static const char ch_dead_mario = 'X';
static const char ch_explosion = '*';