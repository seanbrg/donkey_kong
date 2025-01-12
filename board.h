#pragma once
#include "utils.h"
#include "point.h"
#include "stage.h"
#include "ghost.h"
/**
 * class representing the game board.
 * handles the board's state, display, and interactions with the game stage.
 */
class Board {
	Stage* stage = nullptr;
	bool colors = true;

	Point start; // must be set in stage

	char currentBoard[MAX_Y][MAX_X + 1]; // current board (without mario)
	char originalStageBoard[MAX_Y][MAX_X + 1]; // board with borders, floors and ladders

	
	
public:

	/**
	 * constructor to initialize the board.
	 * @param _stage: pointer to the initial stage.
	 */
	Board(Stage* _stage, bool _colors);

	/**
	 * default constructor.
	 */
	Board() = default;

	
	/**
	 * resets the board to the initial stage.
	 * @param _stage: pointer to the stage to reset to.
	 */
	void reset(const Stage* _stage = nullptr);

	/**
	 * prints the current state of the board.
	 */
	void print() const;
	
	/**
	 * adds a new stage to the board.
	 * @param _stage: pointer to the new stage to add.
	 */
	void addStage(Stage* const _stage);
	
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
	* gets the starting point of the player.
	* @return the starting point as a Point object.
	*/
	Point startingPoint() const { return stage->startingPoint(); }

	/**
	* gets the first location of the hammer.
	* @return the hammer location as a Point object.
	*/
	Point hammerPoint() const { return stage->hammerPoint(); }

	void load(const std::string& fileName);
};

