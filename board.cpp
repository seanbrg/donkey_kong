#include <cstring>
#include <iostream>
#include <fstream>
#include "board.h"
#include "stage.h"
#include "utils.h"
#include "ghost.h"

using namespace colors;

Board::Board(Stage* _stage, bool _colors) : stage(_stage), colors(_colors)
{
	/*for (int x = 0; x <= MAX_X - MIN_X; x++)
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

	reset(stage);*/
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
void Board::load(const std::string& fileName)
{
	std::ifstream screen_file(fileName);
	if (!screen_file.is_open()) {
		std::cerr << "Error: Unable to open the file: " << fileName << std::endl;

		return;
	}
	int curr_row = 0;
	int curr_col = 0;
	char c;
	while (!screen_file.get(c).eof() && curr_row < MAX_Y) {
		if (c == '\n') {
			if (curr_col < MAX_X) {
				// add spaces for missing cols
				#pragma warning(suppress : 4996) // to allow strcpy
				strcpy(originalStageBoard[curr_row] + curr_col, std::string(MAX_X - curr_col - 1, ' ').c_str());
			}
			++curr_row;
			curr_col = 0;
			continue;
		}
		if (curr_col < MAX_X) {
			originalStageBoard[curr_row][curr_col] = c;

			Point position(curr_col, curr_row);
			switch (c) {
			case ch_mario:
				stage->setStartingPoint(position);
				originalStageBoard[curr_row][curr_col] = ' ';
				break;
			case ch_hammer_dropped:
				stage->setHammerPoint(position);
				originalStageBoard[curr_row][curr_col] = ' ';
				break;
			case ch_dk:
				stage->setDkPoint(position);

				break;
			case ch_pauline:
				stage->setWinPoint(position);
				break;
			case ch_ghost:
				stage->addGhost(Ghost(position, RIGHT, this));
				originalStageBoard[curr_row][curr_col] = ' ';
				break;
			}
			++curr_col;
		}
	}
	int last_row = (curr_row < MAX_Y ? curr_row : MAX_Y - 1);
	// add a closing frame
	// first line
	#pragma warning(suppress : 4996) // to allow strcpy
	strcpy(originalStageBoard[0], std::string(MAX_X, ch_border).c_str());
	originalStageBoard[0][MAX_X] = '\n';
	// last line
	#pragma warning(suppress : 4996) // to allow strcpy
	strcpy(originalStageBoard[last_row], std::string(MAX_X, ch_border).c_str());
	originalStageBoard[last_row][MAX_X] = '\0';
	// first col + last col
	for (int row = 1; row < last_row; ++row) {
		originalStageBoard[row][0] = ch_border;
		originalStageBoard[row][MAX_X - 1] = ch_border;
		originalStageBoard[row][MAX_X] = '\n';
	}
}
