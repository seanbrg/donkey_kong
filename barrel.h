#pragma once
#include <Windows.h>
#include "utils.h"
#include "point.h"
#include "Board.h"

using namespace keys;

/**
 * class representing a barrel in the game.
 * the barrel can move, fall, explode, and interact with the board.
 */
class Barrel
{
	Point pos;
	Key dir;
	Board* pBoard = nullptr;
	bool active = true;
	bool explode = false;
	int fall_counter = 0;

public:

	/**
	 * constructor to initialize a barrel with a position, direction, and board reference.
	 * @param _pos: initial position of the barrel.
	 * @param _dir: initial direction of the barrel.
	 * @param _board: pointer to the game board.
	 */
	Barrel (const Point& _pos, Key _dir, Board* _board) : pos(_pos), dir(_dir), pBoard(_board) {}

	/**
	 * default constructor.
	 */
	Barrel() = default;

	/**
	 * moves the barrel based on its current state and the board.
	 */
	void move();

	/**
	 * gets the current position of the barrel.
	 * @return the position of the barrel as a Point object.
	 */
	Point getPos() const { return pos; }

	/**
	 * draws the barrel on the board.
	 */
	void draw(char ch = ch_barrel) const {
		pBoard->drawChar(ch, pos);
	}

	/**
	 * draws the explosion effect for the barrel.
	 */
	void drawExplosion() const;

	/**
	 * erases the barrel from the board and restores the character at the
	 * barrel's position to the original board state.
	 */
	void erase() const { pBoard->restoreChar(pos); }
	
	/**
	 * checks if the barrel is exploding.
	 * @return true if the barrel is exploding, false otherwise.
	 */
	bool isExploding() const { return explode; }

	/**
	 * checks if the barrel is active.
	 * @return true if the barrel is active, false otherwise.
	 */
	bool exists() const { return active; }
};

