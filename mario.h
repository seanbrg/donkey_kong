#pragma once
#include <Windows.h>
#include <iostream>
#include "utils.h"
#include "point.h"
#include "board.h"

using namespace keys;

/**
 * represents mario - the player - and handles movement and interactions with the game board.
 */
class Mario
{
	Point pos;				// current position
	Key dir = STAY;			// direction of next movement
	Key jump_dir = STAY;	// direction of jump
	int jump_counter = 0;	// phase of jump (from 2 to 0)
	int fall_counter = 0;	// height of current fall
	bool jumping = false;
	bool climbing = false;
	Board* pBoard = nullptr;

public:
	
	/**
	 * sets the starting position of mario.
	 * @param _pos: the starting position of mario.
	 */
	void setStart(const Point& _pos) { pos = _pos; }
	
	/**
	 * retrieves mario's current position.
	 * @return the current position of mario.
	 */
	Point getPos() const { return pos; }
	
	/**
	 * draws mario at his current position.
	 * @param ch: the character used to represent mario on the board.
	 */
	void draw(char ch = ch_mario) const { pBoard->drawChar(ch, pos);  }
	
	/**
	 * draws mario in his "dead" state.
	 */
	void drawDead() const { draw(ch_dead_mario); }
	
	/**
	 * erases mario from his current position on the board.
	 */
	void erase() const { pBoard->restoreChar(pos); }
	
	/**
	 * processes a key press to change mario's movement direction.
	 * @param key: the key pressed by the player.
	 */
	void keyPressed(char key);
	
	/**
	 * moves mario based on his current state and checks for valid positions.
	 * @return true if mario is still alive after the move, false if he dies.
	 * this function can only register death from fall damage.
	 */
	bool move();
	
	/**
	 * resets mario's position and directions to the starting point on the board.
	 */
	void reset();
	
	/**
	 * assigns the board to mario and initializes his position.
	 * @param board: the game board.
	 */
	void setBoard(Board* board) {
		pBoard = board;
		pos = pBoard->startingPoint();
	}
};

