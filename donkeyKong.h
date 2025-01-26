#pragma once
#include <iostream>
#include <list>
#include "point.h"
#include "utils.h"
#include "entity.h"

class Board;

class DonkeyKong
{
	Point pos;
	Board* pBoard;
	bool twice_mode; // for harder difficulty
	utils::Key barrels_dir;

public:

	DonkeyKong(Point _pos, Board* _board, bool _twice = false, utils::Key _dir = utils::Key::LEFT) :
		pos(_pos), pBoard(_board), twice_mode(_twice), barrels_dir(_dir) {}

	DonkeyKong() = default;

	void spawnBarrels(std::list<EntityPtr>& entities);
};

