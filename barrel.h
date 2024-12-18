#pragma once
#include <Windows.h>
#include "utils.h"
#include "point.h"
#include "Board.h"

using namespace keys;
using namespace colors;

class Barrel
{
	Point pos;
	Key dir;
	Board* pBoard = nullptr;
	bool active = true;
	bool explode = false;
	int fall_counter = 0;
public:
	Barrel(Point _pos, Key _dir, Board* _board) : pos(_pos), dir(_dir), pBoard(_board) {}
	Barrel() = default;

	void move();
	Point getPos() { return pos; }
	void draw() const;
	void drawExplosion() const;
	void erase() {
		pBoard->restoreChar(pos);
	}
	bool exploding() { return explode; }
	bool exists() { return active; }
};

