#pragma once
#include <iostream>

#include "utils.h"
#include "point.h"
#include "board.h"
#include "mario.h"
#include "stage.h"
#include "barrel.h"

/**
 * holds and manages the main game logic of the donkey kong game.
 */
class Game
{
	int lives = 3;
	int num_barrels = 0;
	bool colors = true;
	int difficulty = 2;

	Mario mario;
	Board board;
	Stage stage;
	std::vector<Barrel> barrels;

public:

	/**
	 * initializes the game with optional color support and difficulty level.
	 * @param _colors: indicates if colors are being used.
	 * @param _difficulty: specifies the difficulty level of the game.
	 */
	Game(bool _colors, int _difficulty) : colors(_colors), difficulty(_difficulty) {}

	/**
	 * runs the main game loop.
	 */
	void run();

	/**
	 * initializes stage 1 with predefined floors and ladders.
	 */
	void initStage1();

	/**
	 * prints the current game status: mario's remaining lives.
	 */
	void printStatus() const;

	/**
	 * spawns barrels near donkey kong with specific behavior based on difficulty.
	 * @param dk: the position of donkey kong.
	 * @param thrown_twice: indicates if barrels are thrown in both directions.
	 */
	void spawnBarrels(const Point& dk, bool thrown_twice = false);
	
	/**
	 * updates the state of all barrels, including handling explosions.
	 * @param alive: a reference to mario's alive status.
	 * becomes false if mario dies in an explosion.
	 */
	void rollBarrels(bool& alive);
	
	/**
	 * resets the game state, including mario, barrels, and the board.
	 */
	void reset();
	
	/**
	 * checks if mario is in the same position as any barrel.
	 * @return true if mario avoids barrels, false if hit.
	 */
	bool checkMarioBarrel() const;
	
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
};

