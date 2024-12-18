#include <cstring>
#include <iostream>

#include "board.h"
#include "stage.h"
#include "utils.h"

using namespace colors;

Board::Board(Stage* _stage, bool _colors) : stage(_stage), colors(_colors)
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

	reset(stage);
}

void Board::addStage(Stage* _stage) {
	if (stage == nullptr) {
		stage = _stage;
		reset(_stage);
		start = _stage->startingPoint();
	}
	else stage->addNextStage(_stage);
}

char Board::getChar(Point pos) const {
	if (0 <= pos.getX() <= MAX_X - MIN_X && 0 <= pos.getY() <= MAX_Y - MIN_Y)
		return currentBoard[pos.getY()][pos.getX()];
}

void Board::drawChar(const char c, Point pos) {
	if (0 <= pos.getX() <= MAX_X - MIN_X && 0 <= pos.getY() <= MAX_Y - MIN_Y) {
		gotoxy(pos.getX() + MIN_X, pos.getY() + MIN_Y);
		std::cout << c;
		currentBoard[pos.getY()][pos.getX()] = c;
	}
}

void Board::restoreChar(Point pos) {
	
	gotoxy(pos.getX() + MIN_X, pos.getY() + MIN_Y);

	//get char of current pos
	char current_char = currentBoard[pos.getY()][pos.getX()];

	if (colors)
		changeColor(current_char);

	std::cout << current_char;
}

void Board::restoreBoardExplosion(Point explosion)
{
	for (int x = 0 - explosion_range; x <= explosion_range; x++) {
		for (int y = 0 - explosion_range; y <= explosion_range; y++) {
			int explosion_x = explosion.getX() + x;
			int explosion_y = explosion.getY() + y;
			restoreChar({ explosion_x, explosion_y });
		}
	}
}

void Board::reset(Stage* _stage)
{
	if (_stage != nullptr) {
		for (int y = 0; y < MAX_Y; y++) {
			memcpy(originalStageBoard[y], blankBoard[y], MAX_X + 1);
		}
		stage->load(originalStageBoard);
	}

	for (int y = 0; y < MAX_Y; y++) {
		memcpy(currentBoard[y], originalStageBoard[y], MAX_X + 1);
	}
}

void Board::print() const {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 

	for (int i = 0; i < MAX_Y; i++) {
		gotoxy(MIN_X, MIN_Y + i);  

		for (int j = 0; j < MAX_X + 1; j++) {
			char current_char = currentBoard[i][j];
			if (colors)
				changeColor(current_char);

			std::cout << current_char;
		}
		if (i < MAX_Y - 1)
			std::cout << '\n';
	}
	SetConsoleTextAttribute(hConsole, WHITE);
}

