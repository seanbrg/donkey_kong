#include "game.h"
#include <Windows.h>
#include <iostream>
#include <chrono>
#include "barrel.h"

using namespace keys;

void Game::run()
{
	system("cls"); // clear screen

	if (fileNames.empty()) {
		std::cout << "ERROR: no screen files found! Please add screen files to the directory.\n";
		_getch();
		return;
	}

	for (const auto& filename : fileNames) {
		board = Board(colors);
		int loaded = board.load(filename);
		if (loaded == EXIT_SUCCESS) {
			board.reset();
			board.print();

			entities = board.getEntities();

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

							moveEntities(alive);

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
					reset();
				}
				printEndGameWindow(victory);
			}

			if (lives == 0) break;
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
		Entity* barrel_left = new Barrel(dk, LEFT, &board);
		Entity* barrel_right = new Barrel(dk, LEFT, &board);

		entities.push_back(barrel_left);
		entities.push_back(barrel_right);
	}
	else { // default
		Entity* barrel_next = new Barrel(dk, next, &board);

		entities.push_back(barrel_next);
		next = (next == LEFT) ? RIGHT : LEFT;
	}
}

void Game::moveEntities(bool& alive)
{
	Point mario_pos = mario.getPos();

	for (auto entity = entities.begin(); entity != entities.end();) {
		(*entity)->erase();
		(*entity)->move(entities);

		Point entity_pos = (*entity)->getPos();
		Point below_mario = mario_pos.neighbor(DOWN);

		if (entity_pos == below_mario || entity_pos == below_mario.neighbor(DOWN)) {
			score += 100;
			printLegend();
		}
		else if (mario_pos == entity_pos) {
			alive = false;
			break;
		}

		Barrel* barrel = dynamic_cast<Barrel*>(*entity);
		if (barrel) {
			if (barrel->isExploding()) {
				barrel->drawExplosion();
				// check if mario is within range of the explosion

				int mario_x = mario_pos.getX();
				int mario_y = mario_pos.getY();
				int explosion_x = entity_pos.getX();
				int explosion_y = entity_pos.getY();
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
				++entity;
			}
			else { // erased
				if (barrel->isExploding())
					board.restoreBoardExplosion(entity_pos);

				delete* entity;
				entity = entities.erase(entity);
			}
		}
		else {
			(*entity)->draw();
			++entity;
		}
	}
}

void Game::reset()
{
	hammer.unequip();
	board.reset();
	entities = board.getEntities();
	board.print();
	printLegend();
	mario.reset();
}

bool Game::checkMarioDeath() const
{
	Point mario_pos = mario.getPos();
	for (auto& entity : entities) {
		if (mario_pos == entity->getPos())
			return false;
	}
	return true;
}

void Game::checkHit()
{
	Point hit0 = hammer.getPos();
	Point hit1 = hammer.getHit();
	bool hit = false;

	auto entity = entities.begin(); // iterator over the entities list
	while (entity != entities.end()) {
		Point barrel_pos = (*entity)->getPos();
		if (barrel_pos == hit0 || barrel_pos == hit1) {
			delete *entity;
			entity = entities.erase(entity);
			score += 300;
			hit = true;
		}
		else ++entity;
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

void Game::printEndGameWindow(bool victory, bool end) const
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
		std::cout << " |                You won!                 | ";
	else
		std::cout << " |                You died.                | ";

	gotoxy(center_x - 22, center_y);
	std::cout << " |             Your score: " << score;
	for (int i = log10(score + 1); i < 14; i++) std::cout << " ";
	std::cout << " | ";
	gotoxy(center_x - 22, center_y + 1);

	if (end)
		std::cout << " |  Press ESC to return to the main menu.  | ";
	else
		std::cout << " |  Press ESC to continue to next stage.   | ";

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
	for (auto& entity : entities)
		entity->draw();
}

void Game::flushInput(char& input)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	FlushConsoleInputBuffer(hInput);

	input = 0;
}

Game::~Game()
{
	for (auto& entity : entities) {
		delete entity;
	}
	entities.clear();
}
