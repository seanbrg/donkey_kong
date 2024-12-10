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

