#pragma once
#include "utils.h"
#include "point.h"
#include "stage.h"

class Board {
	Stage* stage = nullptr;
	Point start; // must be set in stage
	char currentBoard[MAX_Y][MAX_X + 1]; // current board (without mario)
	char blankBoard[MAX_Y][MAX_X + 1]; // board with only borders
	char originalStageBoard[MAX_Y][MAX_X + 1]; // board with borders, floors and ladders

	


	
public:
	Board(Stage* _stage = nullptr);
	void reset(Stage* _stage = nullptr);
	void print() const;
	void addStage(Stage* _stage);
	char getChar(Point pos) const;
	void drawChar(const char c, Point pos);
	void restoreChar(Point pos);
	void restoreBoardExplosion(Point explosion);
	Point startingPoint() const { return stage->startingPoint(); }
};

