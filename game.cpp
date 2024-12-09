#include "game.h"

void Game::run()
{
	Stage stage1; // TO DO: a function in Game class that builds entire stage1 with preset values
	Floor floor1 = {{ 3, 22 }, '=', 65 };
	stage1.addFloor(floor1);
	board.addStage(&stage1);

	ShowConsoleCursor(false);
	board.print();
	
	mario.setBoard(board);

	bool game_running = true;
	while (game_running) {
		mario.draw();
		if (_kbhit()) {
			char key = _getch();

			if (key == 27) break;
			mario.keyPressed(key);
		}
		Sleep(50);
		mario.erase();
		mario.move();
	}
	gotoxy(0, MAX_Y);
}