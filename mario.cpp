#include "mario.h"
#include "utils.h"

using namespace keys;

void Mario::keyPressed(char key)
{
	switch (std::tolower(key)) {
	case((char)LEFT):
		if (!climbing) dir = LEFT;
		break;
	case((char)RIGHT):
		if (!climbing) dir = RIGHT;
		break;
	case((char)STAY):
		dir = STAY;
		break;
	case((char)UP):
		if (pBoard->getChar(pos) == ch_ladder) {
			dir = UP; // start climbing up
			climbing = true;
		}
		else if (pBoard->getChar(pos.down()) != ' ') {
			jump_counter = 2; // start jumping
			jump_dir = (dir == STAY) ? UP : dir; // set direction of jump
			jumping = true;
		}
		break;
	case((char)DOWN):
		if (pBoard->getChar(pos.down()) == ch_ladder) {
			dir = DOWN; // start climbing down
			climbing = true;
		}
		break;
	}
	return;
}

bool Mario::move()
{
	Point new_pos;
	bool alive = true;

	if (jumping) {
		if (jump_dir == UP) new_pos = pos.up();
		else {
			new_pos = (jump_dir == RIGHT) ? pos.right() : pos.left();
			new_pos = (jump_counter == 2) ? new_pos.up() : new_pos.down();
		}
		jump_counter--;
		if (jump_counter == 0) jumping = false;
	}
	else {
		if (pBoard->getChar(pos.down()) == ' ') {  // fall
			fall_counter++;
			new_pos = pos.down();
		}
		else {
			if (fall_counter >= 5) alive = false;
			fall_counter = 0;
			switch (dir) {
			case(LEFT): 
				new_pos = pos.left();
				break;
			case(RIGHT):
				new_pos = pos.right();
				break;
			case(STAY):
				new_pos = pos;
				break;
			case(UP): 
				new_pos = pos.up();
				break;
			case(DOWN):
				new_pos = pos.down();
				break;
			}
		}
	}
	char new_tile = pBoard->getChar(new_pos);

	if (new_tile != ch_ladder) {
		if (climbing) {
			climbing = false;
			dir = STAY;
		}
		if (new_tile != ' ') {
			new_pos = pos;
			if (new_tile == 'O') alive = false;
		}
	}
	pos = new_pos;
	return alive;
}