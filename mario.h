#pragma once
#include <iostream>
#include "utils.h"
#include "point.h"
#include "board.h"

using namespace keys;

class Mario
{
	struct Direction { int x, y; }; // private struct for changing directions easily

	Point pos; // get starting position from board
	Key dir = STAY; // direction of next movement
	Key jump_dir = STAY; // direction of jump: gets initialized when used
	char ch = '@';
	int jump_counter = 0; // phase of jump ; from 2 to 0
	int fall_counter = 0; // height fallen
	bool jumping = false;
	bool climbing = false;
	Board* pBoard = nullptr;

public:
	void setStart(Point _pos) { pos = _pos; }
	Point getPos() { return pos; }
	void draw() const {
		gotoxy(pos.getX() + MIN_X, pos.getY() + MIN_Y);
		std::cout << ch;
	}
	void erase() {
		pBoard->restoreChar(pos);
	}
	void keyPressed(char key);
	bool move();
	void reset() {
		pos = pBoard->startingPoint();
		dir = STAY;
	}
	void setBoard(Board& board) {
		pBoard = &board;
		pos = board.startingPoint();
	}
};

