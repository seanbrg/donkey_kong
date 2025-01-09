#include "game.h"
#include <Windows.h>
#include <iostream>

using namespace keys;

void Game::run()
{
	system("cls"); // clear screen
	initStage1();

	board = Board(&stage, colors);
	ghosts = stage.getGhosts();

	ShowConsoleCursor(false);
	board.print();
	printLegend();

	mario.setBoard(&board);
	hammer.setBoard(&board);
	hammer.setMario(&mario);

	bool victory = false;
	bool skip_ending = false; // for immediately ending the game if needed
	Point pauline_pos = stage.winPoint();
	int frame = 0; // for controlling when a barrel spawns
	char key = 0;  // for player input

	while (lives > 0 && !victory) {
		Point mario_pos = mario.getPos();
	
		mario.draw();
		if (_kbhit()) {
			key = _getch();

			if (key == ESC)
				pause(skip_ending);
			if (skip_ending) break;

			mario.keyPressed(key);
		}

		/*************************************/
		Sleep(250 - difficulty * 50); // game speed
		
		if (mario_pos == pauline_pos) { // victory condition
			victory = true;
		}
		else { // move mario and barrels, reset board if he dies at any point
			mario.erase();
			hammer.erase();
			bool alive = mario.move(); // death by fall damage?

			if (mario_pos == hammer.getPos())
				hammer.equip();
			hammer.draw();

			if (alive) {
				alive = checkMarioDeath(); // death by moving into a barrel?
				if (alive) {
					if (frame % (20 - difficulty * 3) == 0) { // spawn barrels at fixed intervals
						spawnBarrels(stage.dkPoint(), difficulty == 3); // double throw for hard diff
					}

					rollBarrels(alive); // death by explosion?
					moveGhosts();

					if (alive)
						alive = checkMarioDeath(); // death by movement of a barrel?
				}
			}

			if (!alive && !debug_mode) { // lower life and reset board
				lives--;
				mario.drawDead();
				Sleep(1400);
				reset();
				hammer.unequip();
				frame = 0;
				flushInput(key);
			}
			frame++;
		}
	}
	if (!skip_ending) // ending window
		printEndGameWindow(victory);
}

void Game::initStage1() // custom built stage 1
{
	stage = Stage({ 4, 22 }, { 40, 2 }, { 40, 5 }, { 33, 22 });

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

	stage.addGhost(Ghost({ 9, 18 }, RIGHT, &board));
	stage.addGhost(Ghost({ 25, 9 }, RIGHT, &board));
	stage.addGhost(Ghost({ 8, 9 }, RIGHT, &board));
	stage.addGhost(Ghost({ 60, 10 }, RIGHT, &board));

}

void Game::printLegend() const
{
	if (colors)
		changeColor('l');
	gotoxy(MIN_X + 2, MIN_Y + 1);
	std::cout << "LIVES: " << lives;
	gotoxy(MIN_X + 2, MIN_Y + 2);
	std::cout << "SCORE: " << score;
	if (colors)
		changeColor(' ');
}

void Game::spawnBarrels(const Point& dk, bool thrown_twice)
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
		if (barrels[i].isExploding()) {
			barrels[i].drawExplosion();
			// check if mario is within range of the explosion
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
		else { // if barrel doesn't exist anymore is erased
			if (barrels[i].isExploding())
				board.restoreBoardExplosion(barrels[i].getPos());

			barrels.erase(barrels.begin() + i);
			num_barrels--;
		}
	}
}

void Game::moveGhosts()
{
	for (auto& ghost : ghosts) {
		ghost.erase();
		ghost.move(ghosts);
		ghost.draw();
	}
}

void Game::reset()
{
	board.reset();
	num_barrels = 0;
	barrels.clear();
	board.print();
	printLegend();
	mario.reset();
}

bool Game::checkMarioDeath() const
{
	Point mario_pos = mario.getPos();
	for (auto& barrel : barrels) {
		if (mario_pos == barrel.getPos())
			return false;
	}
	for (auto& ghost : ghosts) {
		if (mario_pos == ghost.getPos())
			return false;
	}
	return true;
}

void Game::printPauseWindow() const
{
	const int center_x = (MAX_X - MIN_X) / 2;
	const int center_y = (MAX_Y - MIN_Y) / 2;

	if (colors)
		changeColor(); // to white

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

void Game::printEndGameWindow(bool victory) const
{
	const int center_x = (MAX_X - MIN_X) / 2;
	const int center_y = (MAX_Y - MIN_Y) / 2;

	if (colors)
		changeColor(); // to white

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
	while (key != ESC) { // wait for input
		key = _getch();
	}
}

void Game::pause(bool& skip_ending)
{
	char key = 0;
	printPauseWindow();
	while (key != ESC && key != '1') { // wait for input
		key = _getch();
	}
	if (key == '1') // return to main menu immediately
		skip_ending = true;

	board.print(); // redraw board over the pause menu
	printLegend();
	mario.draw();
	for (auto& barrel : barrels)
		barrel.draw();
}

void Game::flushInput(char& input)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	FlushConsoleInputBuffer(hInput);

	input = 0;
}
