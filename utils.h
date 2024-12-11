#pragma once
#include <iostream>
#include <conio.h> // for keyboard control
#include <Windows.h> // for sleep

void gotoxy(int x, int y);

void ShowConsoleCursor(bool showFlag);

enum class eKeys { LEFT = 'a', RIGHT = 'd', UP = 'w', DOWN = 'x', STAY = 's', ESC = 27 };

static constexpr int MIN_X = 3;
static constexpr int MIN_Y = 1;
static constexpr int MAX_X = 83;
static constexpr int MAX_Y = 26;

static const char ch_border = 'Q';
static const char ch_ladder = 'H';
static const char ch_floor_flat = '=';
static const char ch_floor_left = '<';
static const char ch_floor_right = '>';
