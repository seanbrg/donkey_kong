#pragma once
#include <Windows.h>
#include <iostream>
#include "utils.h"
#include "point.h"
#include "board.h"

/**
 * represents mario - the player - and handles movement and interactions with the game board.
 */
class Mario
{
	Point pos;											// current position
	utils::Key dir = utils::Key::STAY;					// direction of next movement
	utils::Key x_axis_dir = utils::Key::RIGHT;			// direction of movement in the x-axis: LEFT or RIGHT
	utils::Key jump_dir = utils::Key::STAY;				// direction of jump
	int jump_counter = 0;								// phase of jump (from 2 to 0)
	int fall_counter = 0;								// height of current fall
	bool jumping = false;
	bool climbing = false;
	Board* board = nullptr;

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
	 * retrieves mario's direction of movement in the x axis.
	 * @return the current direction in x axis (or last direction that existed).
	 */
	utils::Key getXaxisDir() const { return x_axis_dir; }

	/**
	 * retrieves Mario's next position according to current movement direction.
	 * @return the next position of mario.
	 */
	Point getNext() const { return pos.neighbor(x_axis_dir); }
	
	/**
	 * draws mario at his current position.
	 * @param ch: the character used to represent mario on the board.
	 */
	void draw(char ch = utils::ch_mario) const { board->drawChar(ch, pos);  }
	
	/**
	 * draws mario in his "dead" state.
	 */
	void drawDead() const { draw(utils::ch_dead_mario); }
	
	/**
	 * erases mario from his current position on the board.
	 */
	void erase() const { board->restoreChar(pos); }
	
	/**
	 * processes a key press to change mario's movement direction.
	 * @param key: the key pressed by the player.
	 */
	void keyPressed(utils::Key key);
	
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
	 * @param pboard: the game board.
	 */
	void setBoard(Board* pboard) {
		board = pboard;
		pos = board->getStart();
	}

	/*
	* @return true if mario is currently falling, false otherwise.
	*/
	bool isFalling() { return fall_counter > 0; }

	/*
	* @return true if mario is currently jumping, false otherwise.
	*/	
	bool isJumping() { return jump_counter > 0 || jumping; }
};

