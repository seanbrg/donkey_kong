#pragma once
#include <iostream>
#include <vector>
#include "point.h"
#include "utils.h"

/**
 * represents a single stage (level) in the game.
 * includes floors, ladders, and key positions such as starting, winning, and donkey kong's position.
 */
class Stage
{
	struct Floor		// inner struct for saving floors
	{
		Point start;	// leftmost point
		char type;		// '<' '>' or '='
		int len;		// length
	};

	Point start_pos;				// player's starting position
	Point win_pos;					// position that must be reached to win
	Point dk_pos;					// position from which barrels spawn
	std::vector<Floor> floors;
	std::vector<Point> ladders;
	Stage* next = nullptr;

public:
	/**
	 * constructs a stage with specified starting, winning, and donkey kong positions.
	 * @param _start: the starting position.
	 * @param _win: the winning position.
	 * @param _dk: donkey kong's position.
	 */
	Stage(const Point& _start, const Point& _win, const Point& _dk) : 
		start_pos(_start), win_pos(_win), dk_pos(_dk) {}
	
	/**
	* default constructor with no data
	*/
	Stage() = default;

	/**
	 * adds a floor to the stage.
	 * @param _start: the starting position of the floor.
	 * @param _type: the type of the floor ('<', '>', or '=').
	 * @param _len: the length of the floor.
	 */
	void addFloor(const Point& _start, char _type, int _len) {
		floors.push_back({ _start, _type, _len });
	}

	/**
	 * adds a ladder to the stage.
	 * @param _ladder: the top position of the ladder (should be on a floor).
	 */
	void addLadder(const Point& _ladder) { ladders.push_back(_ladder); }
	
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
	 * retrieves the winning position of this stage.
	 * @return the winning position as a point.
	 */
	Point winPoint() const { return win_pos; }
	
	/**
	 * retrieves the position of donkey kong in this stage.
	 * @return the donkey kong position as a point.
	 */
	Point dkPoint() const { return dk_pos; }
};

