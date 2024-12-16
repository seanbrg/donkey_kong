#include "game.h"
#include <Windows.h>
#include <iostream>


using namespace keys;

void Game::run()
{
	system("cls");
	initStage1();
	board.addStage(&stage);

	ShowConsoleCursor(false);
	board.print();
	printStatus();

	mario.setBoard(&board);

	bool victory = false;
	bool skip_ending = false; // for immediately ending the game if needed
	Point pauline = stage.winPoint();
	int frame = 0; // for controlling when a barrel spawns

	while (lives > 0 && !victory) {
		mario.draw();
		if (_kbhit()) {
			char key = _getch();

			if (key == ESC) { // pause game
				key = 0;
				printPauseWindow();
				while (key != ESC && key != '1') {
					key = _getch();
				}
				if (key == '1') {
					skip_ending = true;
					break;
				}
				unpause();
			}
			mario.keyPressed(key);
		}
		Sleep(240 - difficulty * 40);
		
		if (mario.getPos() == pauline.neighbor(LEFT) || mario.getPos() == pauline.neighbor(RIGHT)) {
			victory = true;
		}
		else {
			mario.erase(); // move mario, reset board if he dies
			bool alive = mario.move();
			if (alive) {
				alive = checkMarioBarrel();
				if (alive) {
					if (frame % (20 - difficulty * 3) == 0) {
						if (difficulty != 4)
							spawnBarrels(stage.dkPoint());
						else spawnBarrels(stage.dkPoint(), true);
					}

					rollBarrels(alive);
					if (alive)
						alive = checkMarioBarrel();
				}
			}

			if (!alive) {
				lives--;
				mario.drawDead();
				Sleep(1400);
				reset();
				frame = 0;
			}
			frame++;
		}
	}
	if (!skip_ending)
		printEndGameWindow(victory);
}

void Game::initStage1() // custom built stage 1
{
	stage = Stage({ 4, 22 }, { 40, 2 }, { 40, 5 });

	static constexpr int NUM_LADDERS = 9;
	Point ladders[NUM_LADDERS]; 
	// format: { (leftmost point), floor type, floor length }
	stage.addFloor({ 1, 23}, ch_floor_flat, 78);
	stage.addFloor({ 69, 18 }, ch_floor_flat, 7);
	stage.addFloor({ 65, 18 }, ch_floor_flat, 3);
	stage.addFloor({ 58, 18 }, ch_floor_flat, 6);
	stage.addFloor({ 55, 11}, ch_floor_left, 17);
	stage.addFloor({ 8, 19}, ch_floor_right, 32);
	stage.addFloor({ 13, 15}, ch_floor_left, 32);
	stage.addFloor({ 3, 10}, ch_floor_right, 36);
	stage.addFloor({ 8, 6}, ch_floor_flat, 60);
	stage.addFloor({ 35, 3 }, ch_floor_flat, 11);

	// the point saved in a ladder must be its highest point (on a floor)
	ladders[0] = { 72, 18 };
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
		barrels.push_back({ dk, LEFT, &board });
		barrels.push_back({ dk, RIGHT, &board });
		num_barrels += 2;
	}
	else { // default
		barrels.push_back({ dk, next, &board });
		next = (next == LEFT) ? RIGHT : LEFT;
		num_barrels++;
	}
}

void Game::rollBarrels(bool& alive)
{
	for (int i = 0; i < num_barrels; i++) {
		barrels[i].erase();
		barrels[i].move();
		if (barrels[i].exploding()) {
			barrels[i].drawExplosion();

			int mario_x = mario.getPos().getX();
			int mario_y = mario.getPos().getY();
			int explosion_x = barrels[i].getPos().getX();
			int explosion_y = barrels[i].getPos().getY();
			if (explosion_x - explosion_range <= mario_x && mario_x <= explosion_x + explosion_range) {
				if (explosion_y - explosion_range <= mario_y && mario_y <= explosion_y + explosion_range) {
					alive = false;
					break;
				}
			}
		}

		if (barrels[i].exists()) {
			barrels[i].draw();
		}
		else {
			if (barrels[i].exploding())
				board.restoreBoardExplosion(barrels[i].getPos());

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

bool Game::checkMarioBarrel()
{
	Point mario_pos = mario.getPos();
	for (auto& barrel : barrels) {
		if (mario_pos == barrel.getPos())
			return false;
	}
	return true;
}

void Game::printPauseWindow()
{
	int center_x = (MAX_X - MIN_X) / 2;
	int center_y = (MAX_Y - MIN_Y) / 2;

	gotoxy(center_x - 22, center_y - 3);
	std::cout << " +-------------------------------------------+ ";
	gotoxy(center_x - 22, center_y - 2);
	std::cout << " |                                           | ";
	gotoxy(center_x - 22, center_y - 1);
	std::cout << " |                Game Paused!               | ";
	gotoxy(center_x - 22, center_y);
	std::cout << " |           Press ESC to continue           | ";
	gotoxy(center_x - 22, center_y + 1);
	std::cout << " |      Or (1) to return to the main menu.   | ";
	gotoxy(center_x - 22, center_y + 2);
	std::cout << " |                                           | ";
	gotoxy(center_x - 22, center_y + 3);
	std::cout << " +-------------------------------------------+ ";
}

void Game::printEndGameWindow(bool victory)
{
	int center_x = (MAX_X - MIN_X) / 2;
	int center_y = (MAX_Y - MIN_Y) / 2;

	gotoxy(center_x - 22, center_y - 3);
	std::cout << " +-----------------------------------------+ ";
	gotoxy(center_x - 22, center_y - 2);
	std::cout << " |                                         | ";

	gotoxy(center_x - 22, center_y - 1);
	if (victory)
		std::cout << " |   Congratulations, you won the game!    | ";
	else
		std::cout << " |                You died.                | ";

	gotoxy(center_x - 22, center_y);
	std::cout << " |                                         | ";
	gotoxy(center_x - 22, center_y + 1);
	std::cout << " |  Press ESC to return to the main menu.  | ";
	gotoxy(center_x - 22, center_y + 2);
	std::cout << " |                                         | ";
	gotoxy(center_x - 22, center_y + 3);
	std::cout << " +-----------------------------------------+ ";


	char key = 0;
	while (key != ESC) {
		key = _getch();
	}
}

void Game::unpause()
{
	board.print();
	printStatus();
	mario.draw();
	for (auto& barrel : barrels)
		barrel.draw();
}
