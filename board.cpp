#include <cstring>
#include <iostream>

#include "board.h"
#include "stage.h"


Board::Board(Stage* _stage) : stage(_stage)
{
	for (int x = 0; x <= MAX_X - MIN_X; x++)
		blankBoard[0][x] = ch_border;

	for (int y = 1; y < MAX_Y - MIN_Y - 1; y++) {
		blankBoard[y][0] = ch_border;
		for (int x = 1; x < MAX_X - MIN_X; x++) {
			blankBoard[y][x] = ' ';
		}
		blankBoard[y][MAX_X - MIN_X] = ch_border;
	}

	for (int x = 0; x <= MAX_X - MIN_X; x++)
		blankBoard[MAX_Y - MIN_Y - 1][x] = ch_border;

	this->reset(stage);
}

void Board::reset(Stage* _stage)
{
	if (_stage != nullptr) {
		for (int y = 0; y < MAX_Y; y++) {
			memcpy(originalStageBoard[y], blankBoard[y], MAX_X + 1);
		}
		this->stage->load(originalStageBoard);
	}

	for (int y = 0; y < MAX_Y; y++) {
		memcpy(currentBoard[y], originalStageBoard[y], MAX_X + 1);
	}
}

void Board::print() const {
	for (int i = 0; i < MAX_Y - 1; i++) {
		gotoxy(MIN_X, MIN_Y + i);
		std::cout << currentBoard[i] << '\n';
	}
	std::cout << currentBoard[MAX_Y - 1];
}


