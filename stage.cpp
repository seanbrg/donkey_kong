#include "stage.h"

void Stage::load(char board[MAX_Y][MAX_X + 1])
{
	for (Floor& floor : floors) {
		int x = floor.start.getX();
		int y = floor.start.getY();

		for (int i = x; i < x + floor.len; i++)
			board[y][i] = floor.type;
	}

	for (Point& ladder : ladders) {
		Point draw = ladder;
		int x = ladder.getX();
		int y = ladder.getY();
		while (board[y + 1][x] == ' ') {
			board[y][x] = ch_ladder;
			draw = draw.down();
			x = draw.getX();
			y = draw.getY();
		}
		board[y][x] = ch_ladder;
	}
	
}
