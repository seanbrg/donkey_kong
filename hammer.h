#pragma once
#include "utils.h"
#include "Point.h"
#include "board.h"
#include "mario.h"

/*
* represents a hammer held by mario in the game and handles most of its functionality
*/
class Hammer
{
	Point pos;
	Point hit_pos;
	bool equipped = false;
	bool hitting = false;
	bool key_hit = false;

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
	Point getHit() const { return hit_pos; }

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
	void unequip();

	/*
	* handle the mechanic of hitting the hammer, including drawing the animation.
	*/
	void hit();

	/*
	* @return whether or not the hammer is currently hitting.
	*/
	bool isHitting() { return key_hit; }
	
	/*
	* draw the hammer, either in its current position or in a specific position for a hit animation.
	* @param draw_pos: the location of the drawing, only used when the hammer is hitting for animations.
	* @param ch: the char to draw, only used for hit animations, otherwise uses ch_hammer_dropped.
	*/
	void draw(Point draw_pos = {0,0}, char ch = utils::ch_hammer_dropped) const;


	/*
	* sets the hit animation of the hammer to begin.
	*/
	void keyPressed() { if (!mario->isFalling() && !hitting && equipped) key_hit = true; }

	/*
	* erase the hammer from its previous position on the board.
	*/
	void erase();
};

