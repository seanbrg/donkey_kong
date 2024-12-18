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

	void reset(const Stage* _stage = nullptr);
	void print() const;
	void addStage(Stage* const _stage);
	char getChar(const Point& pos) const;
	void restoreChar(const Point& pos) const;
	void restoreBoardExplosion(const Point& explosion) const;
	bool isColor() const { return colors; }
	void drawChar(char c, const Point& pos) const;
	Point startingPoint() const { return stage->startingPoint(); }
};

