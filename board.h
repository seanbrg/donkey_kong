#pragma once
#include <iostream>
#include <vector>

#include "utils.h"
#include "point.h"


/**
 * represents the game board.
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

	std::vector<Point> ghost_locs;
	std::vector<Point> big_ghost_locs;

	char currentBoard[utils::MAX_Y][utils::MAX_X + 1]; // current board (without mario, hammer and entities)
	char originalStageBoard[utils::MAX_Y][utils::MAX_X + 1]; // original board of current stage

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
	/**
	* loads the board layout from a file.
	* @param fileName The name of the file containing the board layout.
	* @return boolean value indicating success or failure in opening the file.
	*/
	bool load(const std::string& fileName);

	/**
	* gets the starting point of the player.
	* @return the starting point as a Point object.
	*/
	Point getStart() const { return start_pos; }
	/**
	 * retrieves the initial position of the hammer on the board.
	 * @return The hammer position as a Point object.
	 */
	Point getHammer() const { return hammer_pos; }

	/**
	 * retrieves the position of Donkey Kong on the board.
	 * @return The Donkey Kong position as a Point object.
	 */
	Point getDK() const { return dk_pos; }

	/**
	 * retrieves the position of the legend on the board.
	 * @return The legend position as a Point object.
	 */
	Point getLegend() const { return legend_pos; }

	/**
	 * retrieves the position of Pauline on the board.
	 * @return The Pauline position as a Point object.
	 */
	Point getPauline() const { return pauline_pos; }

	/**
	 * retrieves the vector of all ghost starting positions in the current stage.
	 * @return A vector of positions representing ghosts.
	 */
	const std::vector<Point>& getGhosts() const { return ghost_locs; }

	/**
	 * retrieves the vector of all big ghost starting positions in the current stage.
	 * @return A vector of positions representing big ghosts.
	 */
	const std::vector<Point>& getBigGhosts() const { return big_ghost_locs; }
};

