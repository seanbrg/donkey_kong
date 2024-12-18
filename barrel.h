#pragma once
#include <Windows.h>
#include "utils.h"
#include "point.h"
#include "Board.h"

using namespace keys;

class Barrel
{
	Point pos;
	Key dir;
	Board* pBoard = nullptr;
	bool active = true;
	bool explode = false;
	int fall_counter = 0;

public:
	Barrel (const Point& _pos, Key _dir, Board* _board) : pos(_pos), dir(_dir), pBoard(_board) {}
	Barrel() = default;

	void move();
	Point getPos() const { return pos; }
	void draw(char ch = ch_barrel) const {
		pBoard->drawChar(ch, pos);
	}
	void drawExplosion() const;
	void erase() const {
		pBoard->restoreChar(pos);
	}
	bool isExploding() const { return explode; }
	bool exists() const { return active; }
};

