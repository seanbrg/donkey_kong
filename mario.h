#pragma once
#include <Windows.h>
#include <iostream>
#include "utils.h"
#include "point.h"
#include "board.h"

using namespace keys;
using namespace colors;

class Mario
{
	struct Direction { int x, y; }; // private struct for changing directions easily

	Point pos; // get starting position from board
	Key dir = STAY; // direction of next movement
	Key jump_dir = STAY; // direction of jump: gets initialized when used
	int jump_counter = 0; // phase of jump ; from 2 to 0
	int fall_counter = 0; // height fallen
	bool jumping = false;
	bool climbing = false;
	Board* pBoard = nullptr;

public:
	void setStart(Point _pos) { pos = _pos; }
	Point getPos() { return pos; }
	void draw(char ch = ch_mario) const;
	void drawDead() {
		draw(ch_dead_mario);
	}
	void erase() {
		pBoard->restoreChar(pos);
	}
	void keyPressed(char key);
	bool move();
	void reset() {
		pos = pBoard->startingPoint();
		dir = STAY;
		fall_counter = 0;
	}
	void setBoard(Board* board) {
		pBoard = board;
		pos = pBoard->startingPoint();
	}
};

