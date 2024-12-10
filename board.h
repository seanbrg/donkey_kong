#pragma once
#include "utils.h"
#include "stage.h"

class Board {
	Stage* stage = nullptr;
	Point start; // must be set in stage
	char currentBoard[MAX_Y][MAX_X + 1]; // +1 for null terminator
	char blankBoard[MAX_Y][MAX_X + 1];
	char originalStageBoard[MAX_Y][MAX_X + 1];
	
public:
	Board(Stage* _stage = nullptr);
	void reset(Stage* _stage);
	void addStage(Stage* _stage) {
		if (stage == nullptr) {
			stage = _stage;
			reset(_stage);
			start = _stage->startingPoint();
		}
		else stage->addNextStage(_stage);
	}
	void print() const;
	char getChar(Point pos) const {
		return currentBoard[pos.y][pos.x];
	}
	void drawChar(const char c, Point pos) {
		gotoxy(pos.x + MIN_X, pos.y + MIN_Y);
		std::cout << c;
		currentBoard[pos.y][pos.x] = c;
	}
	void restoreChar(Point pos) {
		gotoxy(pos.x + MIN_X, pos.y + MIN_Y);
		std::cout << currentBoard[pos.y][pos.x];
	}
	Point startingPoint() { return stage->startingPoint(); }
};

