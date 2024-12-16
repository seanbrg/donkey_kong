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

	Mario mario;
	Board board;
	Stage stage;
	std::vector<Barrel> barrels;
public:

	void run();
	void initStage1();
	void printStatus();
	void spawnBarrels(Point dk, bool thrown_twice = false);
	void rollBarrels();
	void reset();
	bool checkMarioBarrel();
};

