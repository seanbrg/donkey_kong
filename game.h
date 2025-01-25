#pragma once
#include <iostream>
#include <list>

#include "utils.h"
#include "point.h"
#include "board.h"
#include "mario.h"
#include "hammer.h"
#include "entity.h"

/**
 * holds and manages the main game logic of the donkey kong game.
 */
class Game
{
private:
	bool colors = true;
	bool save_mode = false;
	bool debug_mode = false; // turn on to make mario immortal
							// WARNING: may cause unexpected behavior

protected:
	int lives = 3;
	int difficulty = 2;
	int score = 0;

	Mario mario;
	Hammer hammer;
	Board board;
	std::list<EntityPtr> entities;
	std::vector<std::string> fileNames;

private:

	/**
	 * displays the pause window with instructions to resume or quit the game.
	 */
	void printPauseWindow() const;

	/**
	 * displays the end-game window indicating victory or defeat.
	 * @param victory: specifies whether the player won the game.
	 */
	void printEndGameWindow(bool victory, bool end = false) const;

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

protected:

	/**
	* processes input by the player.
	* @param key: character that was recieved as input.
	*/
	void input(char key);

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
	 * updates the position of all entities.
	 * @param alive: a reference to mario's alive status.
	 * becomes false if mario dies from stepping on an entity.
	 */
	void moveEntities(bool& alive);
	
	/**
	* resets the entities list of the current stage to its starting position
	* based on the list of ghost locs saved in the board.
	*/
	void resetEntities();

	/**
	* resets the game state, including mario, barrels, and the board.
	*/
	void reset();

	/**
	 * checks if mario is in the same position as any barrel or ghost.
	 * @return true if mario avoids barrels or ghosts, false if hit.
	 */
	bool checkMarioDeath() const;

	/*
	* check if any entity was hit by the hammer's current hitting animation.
	*/
	void checkHit();

public:

	/**
	 * initializes the game with several options.
	 * @param _files: string vectors of .screen file names for the game to run.
	 * @param _clr: indicates if colors are being used.
	 * @param _dif: specifies the difficulty level of the game.
	 * @param _sv: indicates if the game is in save mode.
	 */
	Game(std::vector<std::string>& _files, bool _clr, int _dif, bool _sv)
		: fileNames(_files), colors(_clr), difficulty(_dif), save_mode(_sv) {}

	/*
	* default constructor for inherited Game objects.
	*/
	Game() = default;

	/**
	 * runs the main game loop.
	 */
	virtual void run();

	/**
	* destructor for game tells the list of entities to clear(), as the list
	* contains smart vectors that need to be destroyed for the entities to be deleted
	*/
	virtual ~Game() { entities.clear(); }
};

