#pragma once
#include <iostream>
#include "utils.h"
#include "point.h"
#include "board.h"



class Mario
{
	struct Direction { int x, y; }; // private struct for changing directions easily

	Point pos; // get starting position from board
	Direction dir = { 0 , 0 }; // direction of next movement
	Direction jump_dir; // direction of jump: gets initialized when used
	char ch = '@';
	int jumps_remaining = 0; // phase of jump ; from 2 to 0
	bool jumping = false;
	bool falling = false;
	bool climbing = false;
	Board* pBoard = nullptr;

public:
	void setStart(Point _pos) { pos = _pos; }
	void draw() const {
		gotoxy(pos.x + MIN_X, pos.y + MIN_Y);
		std::cout << ch;
	}
	void erase() {
		pBoard->restoreChar(pos);
	}
	void keyPressed(char key);
	void move();
	void setBoard(Board& board) {
		pBoard = &board;
		pos = board.startingPoint();
	}
};

