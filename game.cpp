#include "game.h"
#include <Windows.h>

using namespace keys;

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

			if (key == ESC) break;
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
	static constexpr int NUM_LADDERS = 7;
	Point ladders[NUM_LADDERS]; 
	// format: { (leftmost point), floor type, floor length }
	stage1.addFloor({1, 23}, ch_floor_flat, 79);
	stage1.addFloor({58, 18}, ch_floor_flat, 14);
	stage1.addFloor({55, 10}, ch_floor_left, 17);
	stage1.addFloor({8, 19}, ch_floor_right, 32);
	stage1.addFloor({13, 15}, ch_floor_left, 32);
	stage1.addFloor({3, 9}, ch_floor_right, 36);
	stage1.addFloor({8, 5}, ch_floor_flat, 59);

	// the point saved in a ladder must be its highest point (on a floor)
	ladders[0] = { 68, 18 };
	ladders[1] = { 59 , 10 };
	ladders[2] = { 65 , 5 };
	ladders[3] = { 38, 19 };
	ladders[4] = { 14 , 15 };
	ladders[5] = { 37 , 9 };
	ladders[6] = { 10 , 5 };

	for (int i = 0; i < NUM_LADDERS; i++)
		stage1.addLadder(ladders[i]);
}