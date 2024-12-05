#include <cstring>
#include <iostream>

#include "board.h"


Board::Board()
{
	floors = new Floor[NUM_FLOORS];

	for (int i = 0; i < NUM_FLOORS; i++) {

	}

	for (int i = 0; i < MAX_Y; i++) {
		memcpy(currentBoard[i], originalBoard[i], MAX_X + 1);
	}
}

Board::~Board()
{
	delete[] floors;
}

void Board::print() const {
	for (int i = 0; i < MAX_Y - 1; i++) {
		std::cout << currentBoard[i] << '\n';
	}
	std::cout << currentBoard[MAX_Y - 1];
}
