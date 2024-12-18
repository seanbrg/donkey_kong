#pragma once
#include "utils.h"
#include "point.h"
#include "stage.h"

class Board {
	Stage* stage = nullptr;
	bool colors = true;

	Point start; // must be set in stage

	char currentBoard[MAX_Y][MAX_X + 1]; // current board (without mario)
	char blankBoard[MAX_Y][MAX_X + 1]; // board with only borders
	char originalStageBoard[MAX_Y][MAX_X + 1]; // board with borders, floors and ladders
	
public:
	Board(Stage* _stage, bool _colors);
	Board() = default;

	void reset(Stage* _stage = nullptr);
	void print() const;
	void addStage(Stage* _stage);
	char getChar(Point pos) const;
	void drawChar(const char c, Point pos);
	void restoreChar(Point pos);
	void restoreBoardExplosion(Point explosion);
	bool isColor() { return colors; }
	Point startingPoint() const { return stage->startingPoint(); }
};

