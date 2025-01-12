#pragma once
#include <iostream>
#include <list>
#include "point.h"
#include "utils.h"
#include "ghost.h"

/**
 * represents a single stage (level) in the game.
 * includes floors, ladders, and key positions such as starting, winning, and donkey kong's position.
 */

class Stage
{
	

	Point start_pos;				// player's starting position
	Point win_pos;					// position that must be reached to win
	Point dk_pos;					// position from which barrels spawn
	Point hammer_pos;				// position of a hammer to be picked up
	std::list<Ghost> ghosts;
	Stage* next = nullptr;

public:
	/**
	 * constructs a stage with specified starting, winning, and donkey kong positions.
	 * @param _start: the starting position.
	 * @param _win: the winning position.
	 * @param _dk: donkey kong's position.
	 */
	Stage(const Point& _start, const Point& _win, const Point& _dk, const Point& _hm) : 
		start_pos(_start), win_pos(_win), dk_pos(_dk), hammer_pos(_hm) {}
	
	/**
	* default constructor with no data
	*/
	Stage() = default;

	
	
	/**
	 * sets the next stage in the sequence.
	 * @param _next: pointer to the next stage.
	 */
	void addNextStage(Stage* _next) { next = _next; }
	
	/**
	 * loads the stage elements (floors, ladders, etc.) into the board representation.
	 * @param board: the board array on which the stage's elements are saved.
	 */
	void load(char board[MAX_Y][MAX_X + 1]);

	/**
	 * retrieves the next stage.
	 * @return pointer to the next stage.
	 */
	Stage* getNext() const { return next; }
	
	/**
	 * retrieves the starting position of the player in this stage.
	 * @return the starting position as a point.
	 */
	Point startingPoint() const { return start_pos; }

	/**
	 * retrieves the first position of the hammer in this stage.
	 * @return the position of the hammer as a point.
	 */
	Point hammerPoint() const { return hammer_pos; }
	
	/**
	 * retrieves the winning position of this stage.
	 * @return the winning position as a point.
	 */
	Point winPoint() const { return win_pos; }
	
	/**
	 * retrieves the position of donkey kong in this stage.
	 * @return the donkey kong position as a point.
	 */
	Point dkPoint() const { return dk_pos; }
	

	/***************************************************************/

	/**
	 * Adds a ghost to the stage.
	 * @param ghost: The ghost to add.
	 */
	void addGhost(const Ghost& ghost) { ghosts.push_back(ghost); }

	/**
	 * Gets the list of ghosts in the stage.
	 * @return A reference to the vector of ghosts.
	 */
	std::list<Ghost>& getGhosts() { return ghosts; }

	/***************************************************************/
	


	void setStartingPoint(Point start_point) { start_pos = start_point; }


	void setHammerPoint(Point hammer_point) { hammer_pos = hammer_point; }


	void setWinPoint(Point win_point) { win_pos = win_point; }


	void setDkPoint(Point dk_point) { dk_pos = dk_point; }
};

