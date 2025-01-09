#pragma once
#include "utils.h"
#include "Point.h"
#include "board.h"
#include "mario.h"

class Hammer
{
	Point pos;
	bool equipped = false;
	Board* board = nullptr;
	Mario* mario = nullptr;

public:

	/**
	 * retrieves the hammer's current position as a dropped item
	 * (not accounting for being held by mario).
	 * @return the current position of the hammer.
	 */
	Point getPos() const { return pos; }

	/**
	 * assigns the board to the hammer and initializes its position.
	 * @param board: the game board.
	 */
	void setBoard(Board* pboard) {
		board = pboard;
		pos = board->hammerPoint();
	}

	void setMario(Mario* pmario) { mario = pmario; }

	/*
	* switches whether the hammer is currently held or not.
	*/
	void equip() { equipped = !equipped; }

	void draw(char ch = ch_hammer) const;
};

