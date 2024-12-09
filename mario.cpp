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
		case('w'):
			if (pBoard->getChar(pos) != 'H' && pBoard->getChar({pos.x , pos.y + 1}) != ' ') {
				jump_spaces = 2;
				jump_dir = dir;
			}
			break;
		}
	}
	return;
}

void Mario::move()
{
	Point newPos;

	if (jump_spaces > 0) {
		if (jump_dir.x == 0 || jump_spaces > 1) // jump in place or first stage of side jump
			jump_dir = { jump_dir.x, -1 };
		else jump_dir = { jump_dir.x, 1 }; // second stage of side jump

		jump_spaces--;
		newPos = { pos.x + jump_dir.x, pos.y + jump_dir.y };
	}
	else {
		if (pBoard->getChar({ pos.x, pos.y + 1 }) == ' ') {
			dir = { 0, 1 };
		}
		else {
            dir = { dir.x, 0 }; // end fall when floor is reached
        }
		newPos = { pos.x + dir.x , pos.y + dir.y };
	}
	if (pBoard->getChar(newPos) != 'Q') 
		pos = newPos;
	
}