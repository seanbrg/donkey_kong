#include "mario.h"
#include "utils.h"

void Mario::keyPressed(char key)
{
	for (size_t i = 0; i < numKeys; i++) {
		switch (std::tolower(key)) {
		case('a'):
			dir = { -1, 0 };
			break;
		case('s'):
			dir = { 0, 0 };
			break;
		case('d'):
			dir = { 1, 0 };
			break;
		}
		return;
		//if (std::tolower(key) == keys[i]) {
		//	dir = directions[i];
		//	return;
		//}
	}
}

void Mario::move()
{
	int newX = pos.x + dir.x;
	int newY = pos.y + dir.y;
	// TODO: add a function in Board to check if the new position is valid by asking the floors
	//		+ use a constant for the wall character
	// TODO: add parameter for falling down, disable move while falling down until standing on floor again
	// TODO: figure out how to jump
	if (pBoard->getChar(newX, newY) == 'Q') {
		dir = { 0, 0 };
	}
	else {
		pos.x = newX;
		pos.y = newY;
	}

}
