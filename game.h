#pragma once
#include "utils.h"
#include "point.h"
#include "board.h"
#include "mario.h"
#include "stage.h"

class Game
{
	int lives = 3;
	Mario mario;
	Board board;
	Stage stage1; // needs to be initiated with initStage1()
	// TO DO: rename 'stage' to 'level' everywhere
public:
	void run();
	void initStage1();
	void printStatus();
};

