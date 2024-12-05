#include "game.h"

void Game::run()
{
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

}
