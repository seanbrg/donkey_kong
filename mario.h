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
	char ch;
	Board* pBoard = nullptr;
	
	void draw(char c) const {
		gotoxy(pos.x, pos.y );
		std::cout << c;
	}

public:
	Mario(Point _pos = { 7, 21 }, char _ch = '@') : ch(_ch), pos(_pos) {}

	void draw() const {
		draw(ch);
	}
	void erase() {
		draw(' ');
	}
	void keyPressed(char key);
	void move();
	void setBoard(Board& board) {
		pBoard = &board;
	}
};

