#pragma once
#include "utils.h"
#include "Point.h"
#include "board.h"
#include "mario.h"

class Hammer
{
	Point pos;
	Point hit;
	bool equipped = false;
	bool key_hit = false;
	bool hitting = false;

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
	 * retrieves the position that the hammer is hitting.
	 * if used when the hammer is actually hitting, it should be one position next to the hammer.
	 * @return the current position of the hammer.
	 */
	Point getHit() const { return hit; }

	/**
	 * assigns the board to the hammer and initializes its position.
	 * @param pboard: the game board.
	 */
	void setBoard(Board* pboard) {
		board = pboard;
		pos = board->getHammer();
	}

	/**
	 * assigns mario to the hammer.
	 * @param pmario: pointer to the mario instance.
	 */
	void setMario(Mario* pmario) { mario = pmario; }

	/*
	* sets the hammer to be equipped by mario.
	*/
	void equip() { equipped = true; }

	/*
	* sets the hammer to be not equipped by mario.
	*/
	void unequip() { 
		equipped = false; 
		hitting = false;
		key_hit = false;
		pos = board->getHammer();
	}

	bool draw();

	void keyPressed() { if (!mario->isFalling() && !hitting && equipped) key_hit = true; }

	void erase();
};

