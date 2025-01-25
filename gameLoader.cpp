#include <filesystem>
#include <Windows.h>
#include <iostream>
#include "gameLoader.h"
#include "game.h"
#include "steps.h"
#include "results.h"
#include "barrel.h"
#include "ghost.h"
#include "bigGhost.h"


void GameLoader::run()
{
	namespace fs = std::filesystem;

	utils::findFiles(fileNames);

	for (auto& screen_file : fileNames) {
		system("cls"); // clear screen

		std::string prefix = screen_file.substr(0, screen_file.rfind('.'));
		std::string steps_filename = prefix + ".steps";
		std::string result_filename = prefix + ".result";
		
		if (!fs::exists(steps_filename)) {
			std::cout << "Missing file " << steps_filename << "!\nPress any button to continue\n";
			_getch();
			continue;
		}
		else if (silent_mode && !fs::exists(result_filename)) {
			std::cout << "Missing file " << result_filename << " for silent mode!\nPress any button to continue\n";
			_getch();
			continue;
		}

		Steps steps_record;
		Results results_record, results_tested;
		size_t point_of_time = 0;

		steps_record.loadSteps(steps_filename); // .steps initialization
		results_record.loadResults(result_filename);
		difficulty = steps_record.getDifficulty();
		srand(steps_record.getRandomSeed());

		board = Board(steps_record.getColors());

		if (!board.load(screen_file))
			continue;
		else { // successfully loaded .screen file: core game loop
			board.reset();
			board.print();
			resetEntities();

			utils::ShowConsoleCursor(false);

			printLegend();

			mario.setBoard(&board);
			hammer.setBoard(&board);
			hammer.setMario(&mario);

			bool victory = false;
			Point pauline_pos = board.getPauline();
			size_t frame = 0; // for controlling barrel spawn

			while ((lives > 0 && !victory) || !steps_record.isEmpty()) {
				Point mario_pos = mario.getPos();
				mario.draw();

				if (steps_record.isNextStep(point_of_time)) {
					char key = steps_record.popStep();
					input(key);
				}

				if (!silent_mode) Sleep(230 - difficulty * 50); // game speed

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

					if (!alive) { // lower life and reset board
						lives--;
						mario.drawDead();
						if (!silent_mode) Sleep(1200);
						reset();
						frame = 0;
						results_tested.addResult(point_of_time, Results::died);
					}
					frame++;
					point_of_time++;
				}
			}

			if (victory) {
				results_tested.addResult(point_of_time, Results::finished);
				int bonus_score = 5000 - 10 * (point_of_time / difficulty);
				score += max(0, bonus_score);
				reset();
			}
			results_tested.addResult(score, Results::score);

			system("cls"); // clear screen
			std::cout << "Loading of game " << prefix << " is done.\n";

			if (silent_mode && results_record.compare(results_tested))
					std::cout << "Results verified successfully.\n";

			std::cout << "Press any key to continue.\n";
			_getch();

			if (lives == 0) break;
		}
	}

	system("cls"); // clear screen
	std::cout << "File loading done.\nExiting...\n\n";
}
