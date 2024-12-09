#pragma once
#include <iostream>
#include "utils.h"
#include "board.h"



class Mario
{
	static constexpr char keys[] = { 'w', 'a', 'x', 'd', 's' };
	static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]);
	// the directions array order is exactly the same as the keys array - must keep it that way
	static constexpr Direction directions[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {0, 0} };

	Point pos;
	Direction dir = { 0 , 0 };
	Direction jump_dir;
	char ch = '@';
	int jump_spaces = 0;
	Board* pBoard = nullptr;

public:
	Mario(Point _pos = { 6, 21 }) : pos(_pos) {}

	void draw() const {
		pBoard->drawChar(ch, pos);
	}
	void erase() {
		pBoard->drawChar(' ', pos);
	}
	void keyPressed(char key);
	void move();
	void setBoard(Board& board) {
		pBoard = &board;
	}
};

