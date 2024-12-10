#include "game.h"
#include <Windows.h>

void Game::run()
{
	initStage1();
	board.addStage(&stage1);

	ShowConsoleCursor(false);
	board.print();
	
	mario.setBoard(board);

	bool game_running = true;
	while (game_running) {
		mario.draw();
		if (_kbhit()) {
			char key = _getch();

			if (key == (char)eKeys::ESC) break;
			mario.keyPressed(key);
		}
		Sleep(100);
		mario.erase();
		mario.move();
	}
	gotoxy(0, MAX_Y);
}

void Game::initStage1() // custom built stage 1
{
	static constexpr int NUM_FLOORS = 7;
	static constexpr int NUM_LADDERS = 7;
	Floor floors[NUM_FLOORS]; // format: { (leftmost point), floor type, floor length }
	Point ladders[NUM_LADDERS]; // the point saved in a ladder must be its highest point (on a floor)

	floors[0] = {{1, 23}, ch_floor_flat, 79};
	floors[1] = {{58, 18}, ch_floor_flat, 14};
	floors[2] = {{55, 10}, ch_floor_left, 17};
	floors[3] = {{8, 19}, ch_floor_right, 32};
	floors[4] = {{13, 15}, ch_floor_left, 32};
	floors[5] = {{3, 9}, ch_floor_right, 36};
	floors[6] = {{8, 5}, ch_floor_flat, 59};

	ladders[0] = { 68, 18 };
	ladders[1] = { 59 , 10 };
	ladders[2] = { 65 , 5 };
	ladders[3] = { 38, 19 };
	ladders[4] = { 14 , 15 };
	ladders[5] = { 37 , 9 };
	ladders[6] = { 10 , 5 };


	for (int i = 0; i < NUM_FLOORS; i++)
		stage1.addFloor(floors[i]);

	for (int i = 0; i < NUM_LADDERS; i++)
		stage1.addLadder(ladders[i]);
}