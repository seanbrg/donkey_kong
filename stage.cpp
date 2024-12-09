#include "stage.h"

void Stage::load(char board[MAX_Y][MAX_X + 1])
{
	
	for (auto& floor : floors) {
		Point start = floor.getStart();
		int len = floor.getLen();
		char type = floor.getType();

		for (int i = start.x; i < start.x + len; i++)
			board[start.y][i] = type;
	}

	// TO DO: a ladder should extend from one floor to the other
	/*
	for (auto& ladder : ladders) {
		Point start = ladder.getStart();
		int ch = ladder.getChar();

		for (int i = start.y - height; i < start.y; i++)
			board[i][start.x] = ch;
	}*/
	
}
