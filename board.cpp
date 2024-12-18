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

void Board::addStage(Stage* const _stage) {
	if (stage == nullptr) {
		stage = _stage;
		reset(_stage);
		start = _stage->startingPoint();
	}
	else stage->addNextStage(_stage);
}

char Board::getChar(const Point& pos) const {
	return currentBoard[pos.getY()][pos.getX()];
}

void Board::drawChar(char c, const Point& pos) const {
	gotoxy(pos.getX() + MIN_X, pos.getY() + MIN_Y);
	if (colors)
		changeColor(c);

	std::cout << c;
}

void Board::restoreChar(const Point& pos) const {
	int x = pos.getX();
	int y = pos.getY();

	gotoxy(x + MIN_X, y + MIN_Y);

	//get char of current pos
	char current_char = currentBoard[y][x];

	if (colors)
		changeColor(current_char);

	std::cout << current_char;
}

void Board::restoreBoardExplosion(const Point& explosion) const
{
	for (int x = 0 - explosion_range; x <= explosion_range; x++) {
		for (int y = 0 - explosion_range; y <= explosion_range; y++) {
			Point former_explosion = { explosion.getX() + x, explosion.getY() + y };
			restoreChar(former_explosion);
		}
	}
}

void Board::reset(const Stage* _stage)
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

