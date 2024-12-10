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

	for (auto& ladder : ladders) {
		Point pos = ladder;
		while (board[pos.y + 1][pos.x] == ' ') {
			board[pos.y][pos.x] = ch_ladder;
			pos.y++;
		}
		board[pos.y][pos.x] = ch_ladder;
	}
	
}
