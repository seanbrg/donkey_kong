#pragma once
#include <iostream>

#include "utils.h"
#include "point.h"
#include "board.h"
#include "mario.h"
#include "stage.h"
#include "barrel.h"

class Game
{
	int lives = 3;
	int num_barrels = 0;
	bool colors;
	int difficulty;

	Mario mario;
	Board board;
	Stage stage;
	std::vector<Barrel> barrels;
public:
	Game(bool _colors = false, int _difficulty = 2) : colors(_colors), difficulty(_difficulty) {
		if (difficulty == 4) lives = 1;
	}

	void run();
	void initStage1();
	void printStatus();
	void spawnBarrels(Point dk, bool thrown_twice = false);
	void rollBarrels();
	void reset();
	bool checkMarioBarrel();
	void printPauseWindow();
	void printEndGameWindow(bool victory);
	void unpause();
};

