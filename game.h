#pragma once
#include "utils.h"
#include "point.h"
#include "board.h"
#include "mario.h"
#include "stage.h"

class Game
{
	Mario mario;
	Board board;
	Stage stage1; // needs to be initiated with initStage1()
	
public:
	Game() {}
	void run();
	void initStage1();
};

