#pragma once
#include "utils.h"
#include "point.h"
#include "ghost.h"

/**
 * class representing the game board.
 * handles the board's state, display, and interactions with the game stage.
 */
class Board {
	bool colors = true;
	bool hammer_in_board = false;

	Point start_pos;
	Point hammer_pos;
	Point legend_pos;
	Point dk_pos;
	Point pauline_pos;

	std::list<Ghost> start_ghosts;

	char currentBoard[MAX_Y][MAX_X + 1]; // current board (without mario, hammer and entities)
	char originalStageBoard[MAX_Y][MAX_X + 1]; // original board of current stage

public:

	/**
	 * constructor to initialize the board.
	 * @param _colors: color mode (for printing in color).
	 */
	Board(bool _colors) : colors(_colors) {}

	/**
	 * default constructor.
	 */
	Board() = default;

	/**
	 * resets the board to the initial stage.
	 */
	void reset();

	/**
	 * prints the current state of the board.
	 */
	void print() const;
	
	/**
	 * retrieves the character at a specified position.
	 * @param pos: the position on the board to query.
	 * @return the character at the specified position.
	 */
	char getChar(const Point& pos) const;
	
	/**
	 * draws a character at a specified position on the board.
	 * @param c: the character to draw.
	 * @param pos: the position to draw the character at.
	 */
	void drawChar(char c, const Point& pos) const;

	/**
	 * restores (prints) the character at a specified position on the board.
	 * @param pos: the position to restore.
	 */
	void restoreChar(const Point& pos) const;
	
	/**
	 * restores all characters that were affected by an explosion.
	 * @param explosion: the center of the explosion.
	 */
	void restoreBoardExplosion(const Point& explosion) const;
	
	/**
	* tells if the board currently uses colors.
	* @return true if colors are used, false if not.
	*/
	bool isColor() const { return colors; }
	
	int load(const std::string& fileName);

	/**
	* gets the starting point of the player.
	* @return the starting point as a Point object.
	*/
	Point getStart() const { return start_pos; }

	/**
	* gets the first location of the hammer.
	* @return the hammer location as a Point object.
	*/
	Point getHammer() const { return hammer_pos; }

	Point getDK() const { return dk_pos; }

	Point getLegend() const { return legend_pos; }

	Point getPauline() const { return pauline_pos; }

	std::list<Ghost>& getGhosts() { return start_ghosts; }

};

