#include "game.h"
#include <Windows.h>
#include <iostream>
#include <chrono>

using namespace keys;

void Game::run()
{
	system("cls"); // clear screen
	std::vector<std::string> fileNames;
	getAllScreenFileNames(fileNames);


	if (fileNames.empty()) {
		std::cout << "ERROR: no screen files found! Please add screen files to the directory.\n";
		_getch();
		return;
	}

	for (const auto& filename : fileNames) {
		board = Board(colors);
		board.load(filename);
		board.reset();
		board.print();


		ghosts = board.getGhosts();

		ShowConsoleCursor(false);

		printLegend();

		mario.setBoard(&board);
		hammer.setBoard(&board);
		hammer.setMario(&mario);

		bool victory = false;
		bool skip_ending = false; // for immediately ending the game if needed
		Point pauline_pos = board.getPauline();
		int frame = 0; // for controlling when a barrel spawns
		char key = 0;  // for player input

		auto start_clk = std::chrono::high_resolution_clock::now();

		while (lives > 0 && !victory) {
			Point mario_pos = mario.getPos();

			mario.draw();
			if (_kbhit()) {
				key = _getch();

				if (key == ESC)
					pause(skip_ending);
				if (skip_ending) break;

				keyPressed(key);
			}


			Sleep(230 - difficulty * 50); // game speed

			if (mario_pos == pauline_pos) { // victory condition
				victory = true;
				break;

			}
			else { // move mario and barrels, reset board if he dies at any point
				mario.erase();
				hammer.erase();
				bool alive = mario.move(); // death by fall damage?

				if (mario_pos == hammer.getPos())
					hammer.equip();

				if (alive) {
					alive = checkMarioDeath(); // check if mario moved into a ghost/barrel
					if (alive) {
						if (frame % (20 - difficulty * 3) == 0) { // spawn barrels at fixed intervals
							spawnBarrels(board.getDK(), difficulty == 3); // double throw for hard diff
						}

						if (hammer.draw()) checkHit(); // check hit if hammer is currently hitting

						rollBarrels(alive);
						moveGhosts(alive);

					}
				}

				if (!alive && !debug_mode) { // lower life and reset board
					lives--;
					mario.drawDead();
					Sleep(1200);
					reset();
					flushInput(key);
					frame = 0;
				}
				frame++;
			}
		}

		auto end_clk = std::chrono::high_resolution_clock::now();

		if (!skip_ending) { // ending window
			if (victory) {
				// duration counts in 0.1 seconds the length of the game.
				// every 1 second below 6 minutes the game is won in is worth 100 bonus score
				std::chrono::duration<double> duration = end_clk - start_clk;
				int bonus_score = 5000 - 100 * (int)duration.count();
				score += max(0, bonus_score);
			}
			printEndGameWindow(victory);
		}


	}
}

void Game::keyPressed(char key)
{
	char low_key = tolower(key);
	if (low_key == 'w' || low_key == 'a' || low_key == 's' || low_key == 'd' || low_key == 'x') {
		mario.keyPressed((Key)low_key);
	}
	else if (low_key == 'p') {
		hammer.keyPressed();
	}
}

void Game::printLegend() const
{
	Point legend = board.getLegend();

	if (colors)
		changeColor('l');
	gotoxy(MIN_X + legend.getX(), MIN_Y + legend.getY());
	std::cout << "LIVES: " << lives;
	gotoxy(MIN_X + legend.getX(), MIN_Y + legend.getY() + 1);
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
	}
	else { // default
		barrels.push_back({ dk, next, &board });
		next = (next == LEFT) ? RIGHT : LEFT;
	}
}

void Game::rollBarrels(bool& alive)
{
	Point mario_pos = mario.getPos();
	auto barrel = barrels.begin(); // iterator over the barrels list

	while (barrel != barrels.end()) {
		barrel->erase();
		barrel->move();

		Point barrel_pos = barrel->getPos();
		Point below_mario = mario_pos.neighbor(DOWN);

		if (barrel_pos == below_mario || barrel_pos == below_mario.neighbor(DOWN)) {
			score += 100;
			printLegend();
		}
		else if (mario_pos == barrel_pos) {
			alive = false;
			break;
		}

		if (barrel->isExploding()) {
			barrel->drawExplosion();
			// check if mario is within range of the explosion

			int mario_x = mario_pos.getX();
			int mario_y = mario_pos.getY();
			int explosion_x = barrel_pos.getX();
			int explosion_y = barrel_pos.getY();
			if (explosion_x - explosion_range <= mario_x && mario_x <= explosion_x + explosion_range) {
				if (explosion_y - explosion_range <= mario_y && mario_y <= explosion_y + explosion_range) {
					alive = false;
					break;
				}
			}
		}

		if (barrel->exists()) { // a barrel stops existing the tick after its death
			barrel->draw();
			++barrel;
		}
		else { // erased
			if (barrel->isExploding())
				board.restoreBoardExplosion(barrel_pos);

			barrel = barrels.erase(barrel);
		}
	}
}

void Game::moveGhosts(bool& alive)
{
	Point mario_pos = mario.getPos();

	for (auto& ghost : ghosts) {
		ghost.erase();
		ghost.move(ghosts);
		ghost.draw();

		Point ghost_pos = ghost.getPos();
		Point below_mario = mario_pos.neighbor(DOWN);

		if (ghost_pos == below_mario || ghost_pos == below_mario.neighbor(DOWN)) {
			score += 100;
			printLegend();
		}
		else if (mario_pos == ghost_pos) {
			alive = false;
			break;
		}
	}
}

void Game::reset()
{
	hammer.unequip();
	board.reset();
	barrels.clear();
	board.print();
	printLegend();
	mario.reset();
	ghosts = board.getGhosts();
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

void Game::checkHit()
{
	Point hit0 = hammer.getPos();
	Point hit1 = hammer.getHit();
	bool hit = false;

	auto barrel = barrels.begin(); // iterator over the barrels list
	while (barrel != barrels.end()) {
		Point barrel_pos = barrel->getPos();
		if (barrel_pos == hit0 || barrel_pos == hit1) {
			barrel = barrels.erase(barrel);
			score += 300;
			hit = true;
		}
		else ++barrel;
	}

	auto ghost = ghosts.begin(); // iterator over the barrels list
	while (ghost != ghosts.end()) {
		Point ghost_pos = ghost->getPos();
		if (ghost_pos == hit0 || ghost_pos == hit1) {
			ghost = ghosts.erase(ghost);
			score += 300;
			hit = true;
		}
		else ++ghost;
	}

	if (hit) printLegend();
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
	std::cout << " |            Final score: " << score;
	for (int i = log10(score + 1); i < 14; i++) std::cout << " ";
	std::cout << " | ";
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
	hammer.draw();
	for (auto& barrel : barrels)
		barrel.draw();
}

void Game::flushInput(char& input)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	FlushConsoleInputBuffer(hInput);

	input = 0;
}

void Game::getAllScreenFileNames(std::vector<std::string>& vec_to_fill) {
	vec_to_fill.push_back("dkong_01.screen");
	//vec_to_fill.push_back("dkong_02.screen");

}