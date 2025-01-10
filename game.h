#pragma once
#include <iostream>
#include <list>

#include "utils.h"
#include "point.h"
#include "board.h"
#include "mario.h"
#include "stage.h"
#include "hammer.h"
#include "barrel.h"
#include "ghost.h"

/**
 * holds and manages the main game logic of the donkey kong game.
 */

class Game
{
	int lives = 3;
	int score = 0;
	bool colors = true;
	int difficulty = 2;
	bool debug_mode = false; // turn on to make mario immortal
							// WARNING: may cause unexpected behavior

	Mario mario;
	Hammer hammer;
	Board board;
	Stage stage;
	std::list<Barrel> barrels;
	std::list<Ghost> ghosts;

public:

	/**
	 * initializes the game with optional color support and difficulty level.
	 * @param _colors: indicates if colors are being used.
	 * @param _difficulty: specifies the difficulty level of the game.
	 */
	Game(bool _clr, int _dif) : colors(_clr), difficulty(_dif) {}

	/**
	 * runs the main game loop.
	 */
	void run();

	/**
	* processes a keyboard hit by the player and handles appropriate input.
	* @param key: character that was recieved as input.
	*/
	void keyPressed(char key);

	/**
	 * initializes stage 1 with predefined floors and ladders.
	 */
	void initStage1();

	/**
	 * prints the legend containing Mario's remaining lives and the current score.
	 */
	void printLegend() const;

	/**
	 * spawns barrels near donkey kong with specific behavior based on difficulty.
	 * @param dk: the position of donkey kong.
	 * @param thrown_twice: indicates if barrels are thrown in both directions.
	 */
	void spawnBarrels(const Point& dk, bool thrown_twice = false);
	
	/**
	 * updates the state of all barrels, including handling explosions.
	 * @param alive: a reference to mario's alive status.
	 * becomes false if mario dies from a barrel.
	 */
	void rollBarrels(bool& alive);

	/**
	 * updates the position of all ghosts.
	 * @param alive: a reference to mario's alive status.
	 * becomes false if mario dies from a ghost.
	 */
	void moveGhosts(bool& alive);
	
	/**
	 * resets the game state, including mario, barrels, and the board.
	 */
	void reset();
	
	/**
	 * checks if mario is in the same position as any barrel or ghost.
	 * @return true if mario avoids barrels or ghosts, false if hit.
	 */
	bool checkMarioDeath() const;

	void checkHit();
	
	/**
	 * displays the pause window with instructions to resume or quit the game.
	 */
	void printPauseWindow() const;
	
	/**
	 * displays the end-game window indicating victory or defeat.
	 * @param victory: specifies whether the player won the game.
	 */
	void printEndGameWindow(bool victory) const;
	
	/**
	 * pauses the game until ESC or 1 is hit. 1 ends the game.
	 * @param skip_ending: becomes true if 1 was hit.
	 */
	void pause(bool& skip_ending);

	/**
	* resets the input from the player and flushes the input buffer.
	* needed to "forget" any unused input from the previous screen/before reset.
	*/
	void flushInput(char& input);
};

