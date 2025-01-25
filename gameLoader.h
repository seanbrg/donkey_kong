#pragma once
#include "game.h"
#include "steps.h"

class GameLoader : public Game
{
private:
	bool silent_mode;
	std::vector<std::string> fileNames;

public:

	/*
	 * initializes the game loader.
	 * @param _silent: indicates whether the loader is in silent mode.
	 */	
	GameLoader(bool _silent = false) : silent_mode(_silent) {}
	
	/*
	* finds valid game files and runs the main game loop for them in load mode.
	*/
	void run() override;
};

