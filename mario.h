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
	void setStart(const Point& _pos) { pos = _pos; }
	Point getPos() const { return pos; }
	void draw(const char ch = ch_mario) const { 
		pBoard->drawChar(ch, pos); 
	};
	void drawDead() const { 
		draw(ch_dead_mario); 
	}
	void erase() const {
		pBoard->restoreChar(pos);
	}
	void keyPressed(char key);
	bool move();
	void reset();
	void setBoard(Board* board) {
		pBoard = board;
		pos = pBoard->startingPoint();
	}
};

