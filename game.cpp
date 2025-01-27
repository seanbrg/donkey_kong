#include <Windows.h>
#include <iostream>
#include <chrono>
#include "game.h"
#include "steps.h"
#include "results.h"
#include "barrel.h"
#include "ghost.h"
#include "bigGhost.h"
#include "donkeyKong.h"

using namespace utils;

void Game::run()
{
	system("cls"); // clear screen

	if (fileNames.empty()) {
		std::cout << "ERROR: no screen files found! Please add screen files to the directory.\n";
		_getch();
		return;
	}

	board = Board(colors);

	for (const auto& screen_file : fileNames) {
		if (board.load(screen_file)) {
			board.reset();
			board.print();
			resetEntities();

			ShowConsoleCursor(false);

			printLegend();

			mario.setBoard(&board);
			hammer.setBoard(&board);
			hammer.setMario(&mario);
			donkeyKong = DonkeyKong(board.getDK(), &board, difficulty == 3);

			bool victory = false;
			bool skip_ending = false; // for immediately ending the game if needed
			Point pauline_pos = board.getPauline();
			size_t point_of_time = 0; // number of iterations since start
			size_t frame = 0; // for controlling barrel spawn
			char key = 0;  // for player input

			Steps steps_saver;
			Results results_saver;
			if (save_mode) {
				long random_seed = static_cast<long>(std::chrono::system_clock::now().time_since_epoch().count());
				steps_saver.setRandomSeed(random_seed);
				steps_saver.setDifficulty(difficulty);
				steps_saver.setColors(colors);
				srand(random_seed);
			}

			while (lives > 0 && !victory) {
				Point mario_pos = mario.getPos();

				mario.draw();
				hammer.draw();
				if (_kbhit()) {
					key = _getch();

					if ((Key)key == Key::ESC) {
						pause(skip_ending);
						if (skip_ending) break;
					}
					else if (save_mode) {
						steps_saver.addStep(point_of_time, (char)key);
					}

					input(key);
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
								donkeyKong.spawnBarrels(entities);
							}

							if (hammer.isHitting()) {
								hammer.hit();
								checkHit();
							}

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

						if (save_mode) results_saver.addResult(point_of_time, Results::died);
					}

					frame++;
					point_of_time++;
				}
			}

			if (!skip_ending) { // ending window
				if (victory) {
					if (save_mode) results_saver.addResult(point_of_time, Results::finished);
					int bonus_score = 5000 - 10 * (point_of_time / difficulty);
					score += max(0, bonus_score);
					reset();
				}
				if (save_mode) results_saver.addResult(score, Results::score);

				bool end = (lives == 0 || screen_file == *(fileNames.end() - 1));
				printEndGameWindow(victory, end);

				if (save_mode) {
					std::string steps_filename = screen_file.substr(0, screen_file.rfind('.')) + ".steps";
					std::string result_filename = screen_file.substr(0, screen_file.rfind('.')) + ".result";
					steps_saver.saveSteps(steps_filename);
					results_saver.saveResults(result_filename);
				}
			}
			else break;

			point_of_time = 0;
			if (lives == 0) break;
		}
		else break;
	}
}

void Game::input(char key)
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

void Game::moveEntities(bool& alive)
{
	Point mario_pos = mario.getPos();

	for (auto entity = entities.begin(); entity != entities.end();) {
		(*entity)->erase();
		(*entity)->move(entities);

		Point entity_pos = (*entity)->getPos();
		Point below_mario = mario_pos.neighbor(Key::DOWN);

		if (mario.isJumping() && (entity_pos == below_mario || entity_pos == below_mario.neighbor(Key::DOWN))) {
			score += 100;
			printLegend();
		}
		else if (mario_pos == entity_pos) {
			alive = false;
			break;
		}

		Barrel* barrel = dynamic_cast<Barrel*>((*entity).get());
		if (barrel) {
			if (barrel->isExploding()) {
				barrel->drawExplosion();
				// check if mario is within range of the explosion

				int mario_x = mario_pos.getX();
				int mario_y = mario_pos.getY();
				int explosion_x = entity_pos.getX();
				int explosion_y = entity_pos.getY();
				if (explosion_x - explosion_range <= mario_x && mario_x <= explosion_x + explosion_range) {
					if (explosion_y - explosion_range <= mario_y && mario_y <= explosion_y) {
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

	resetEntities();

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
	if (end)
		std::cout << " |            Final score: " << score;
	else
		std::cout << " |          Current score: " << score;

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
	while ((Key)key != Key::ESC) { // wait for input
		key = _getch();
	}
}

void Game::pause(bool& skip_ending)
{
	char key = 0;
	printPauseWindow();
	while ((Key)key != Key::ESC && key != '1') { // wait for input
		key = _getch();
	}
	if (key == '1') // return to main menu immediately
		skip_ending = true;

	board.print(); // redraw board over the pause menu
	printLegend();
	mario.draw();
	hammer.draw(hammer.getPos());
	for (auto& entity : entities)
		entity->draw();
}

void Game::flushInput(char& input)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	FlushConsoleInputBuffer(hInput);

	input = 0;
}

void Game::resetEntities()
{
	const std::vector<Point> ghost_locs = board.getGhosts();
	const std::vector<Point> big_ghost_locs = board.getBigGhosts();
	entities.clear(); // EntityPtr are shared pointers with destructors for the entities

	for (auto& pos : ghost_locs) {
		EntityPtr new_ghost = (EntityPtr)new Ghost(pos, Key::LEFT, &board);
		entities.push_back(new_ghost);
	}
	for (auto& pos : big_ghost_locs) {
		EntityPtr new_big_ghost = (EntityPtr)new BigGhost(pos, Key::LEFT, &board);
		entities.push_back(new_big_ghost);
	}
}