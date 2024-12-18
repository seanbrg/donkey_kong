#pragma once
#include <iostream>
#include <conio.h> // for keyboard control
#include <Windows.h> // for sleep

/**
 * moves the console cursor to a specific (x, y) position on the screen.
 * @param x: the x-coordinate of the cursor position.
 * @param y: the y-coordinate of the cursor position.
 */
void gotoxy(int x, int y);

/**
 * shows or hides the console cursor.
 * @param showFlag: a boolean flag indicating whether to show (true) or hide (false) the cursor.
 */
void ShowConsoleCursor(bool showFlag);

/**
* changes the console writing color to a color appropriate for the char specified.
* @param type: a type of char that is specified to have a unique color.
* this includes floors, ladders, mario, donkey kong, pauline and more.
*/
void changeColor(char type = ' ');

namespace keys {
	enum Key { // defines key mappings for movement and control in the game.
		LEFT = 'a',
		RIGHT = 'd',
		UP = 'w',
		DOWN = 'x',
		STAY = 's',
		ESC = 27
	};
};

namespace colors {
	enum Color { // defines the color mappings for console output.
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

// constants for game boundaries and elements:
static constexpr int MIN_X = 0;
static constexpr int MIN_Y = 0;
static constexpr int MAX_X = 79;
static constexpr int MAX_Y = 25;
static const int explosion_range = 2;

// printed characters of all game elements:
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