#include "game.h"
#include <Windows.h>
#include <iostream>


using namespace keys;

void Game::run()
{
	initStage1();
	board.addStage(&stage);

	ShowConsoleCursor(false);
	board.print();
	printStatus();

	mario.setBoard(&board);

	bool victory = false;
	Point pauline = stage.winPoint();
	int frame = 0;

	while (lives > 0 && !victory) {
		mario.draw();
		if (_kbhit()) {
			char key = _getch();

			if (key == ESC) break;
			mario.keyPressed(key);
		}
		Sleep(150);
		
		if (mario.getPos() == pauline.neighbor(LEFT) || mario.getPos() == pauline.neighbor(RIGHT)) {
			victory = true;
		}
		else {
			mario.erase(); // move mario, reset board if he dies
			bool alive;
			alive = mario.move();

			if (frame % 15 == 0)
				spawnBarrels(stage.dkPoint());
			//if (frame % 2 == 0)
			rollBarrels(alive);

			if (!alive) {
				lives--;
				reset();
			}
			frame++;
		}
	}
	gotoxy(0, MAX_Y);
}

void Game::initStage1() // custom built stage 1
{
	stage = Stage({ 4, 22 }, { 40, 2 }, { 40, 5 });

	static constexpr int NUM_LADDERS = 9;
	Point ladders[NUM_LADDERS]; 
	// format: { (leftmost point), floor type, floor length }
	stage.addFloor({1, 23}, ch_floor_flat, 79);
	stage.addFloor({58, 18}, ch_floor_flat, 14);
	stage.addFloor({55, 11}, ch_floor_left, 17);
	stage.addFloor({8, 19}, ch_floor_right, 32);
	stage.addFloor({13, 15}, ch_floor_left, 32);
	stage.addFloor({3, 10}, ch_floor_right, 36);
	stage.addFloor({8, 6}, ch_floor_flat, 59);
	stage.addFloor({ 35, 3 }, ch_floor_flat, 10);

	// the point saved in a ladder must be its highest point (on a floor)
	ladders[0] = { 68, 18 };
	ladders[1] = { 59 , 11 };
	ladders[2] = { 65 , 6 };
	ladders[3] = { 38, 19 };
	ladders[4] = { 14 , 15 };
	ladders[5] = { 37 , 10 };
	ladders[6] = { 10 , 6 };
	ladders[7] = { 36 , 3 };
	ladders[8] = { 44 , 3 };

	for (int i = 0; i < NUM_LADDERS; i++)
		stage.addLadder(ladders[i]);
}

void Game::printStatus()
{
	gotoxy(MIN_X + 2, MIN_Y + 1);
	std::cout << "LIVES: " << lives;
}

void Game::spawnBarrels(Point dk, bool thrown_twice)
{
	static Key next = LEFT;
	if (thrown_twice) { // option for harder difficulty
		barrels.push_back({ dk.neighbor(LEFT), LEFT, &board });
		barrels.push_back({ dk.neighbor(RIGHT), RIGHT, &board });
		num_barrels += 2;
	}
	else { // default
		barrels.push_back({ dk.neighbor(next), next, &board });
		next = (next == LEFT) ? RIGHT : LEFT;
		num_barrels++;
	}
}

void Game::rollBarrels(bool &alive)
{
	for (int i = 0; i < num_barrels; i++) {
		barrels[i].erase();
		barrels[i].move();

		if (barrels[i].exists()) {
			barrels[i].draw();
			if (barrels[i].getPos() == mario.getPos()) {
				alive = false;
				break;
			}
		}
		else {
			barrels.erase(barrels.begin() + i);
			num_barrels--;
		}
	}
}

void Game::reset()
{
	board.reset();
	mario.reset();
	num_barrels = 0;
	barrels.clear();
	board.print();
	printStatus();
}
