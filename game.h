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
	bool colors = true;
	int difficulty = 2;

	Mario mario;
	Board board;
	Stage stage;
	std::vector<Barrel> barrels;
public:
	Game(bool _colors, int _difficulty) : colors(_colors), difficulty(_difficulty) {}

	void run();
	void initStage1();
	void printStatus() const;
	void spawnBarrels(const Point& dk, bool thrown_twice = false);
	void rollBarrels(bool& alive);
	void reset();
	bool checkMarioBarrel() const;
	void printPauseWindow() const;
	void printEndGameWindow(bool victory) const;
	void unpause() const;
};

