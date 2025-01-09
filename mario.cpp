#include "mario.h"
#include "utils.h"

using namespace keys;

void Mario::keyPressed(Key key)
{
	if (key == UP && board->getChar(pos) == ch_ladder) {
		climbing = true; // climb up
		dir = key;
	}
	else if (key == DOWN && board->getChar(pos.neighbor(DOWN)) == ch_ladder) {
		climbing = true; // climb down
		dir = key;
	}
	else if (key == UP && board->getChar(pos.neighbor(DOWN)) != ' ') {
		jump_counter = 2; // jump
		jump_dir = (dir == STAY) ? UP : dir; // set direction of jump
		jumping = true;
	}
	else if (key == RIGHT || key == LEFT || key == STAY) {
		dir = (!climbing) ? key : STAY;
		if (dir == LEFT || dir == RIGHT) 
			x_axis_dir = dir;
	}
}

bool Mario::move()
{
	Point new_pos;

	if (board->getChar(pos.neighbor(DOWN)) != ' ' && fall_counter > 0) {
		if (fall_counter >= 5)
			return false;
		fall_counter = 0;
	}

	if (jumping) { // jumping logic
		new_pos = pos.neighbor(jump_dir);
		if (jump_dir != UP)
			new_pos = (jump_counter == 2) ? new_pos.neighbor(UP) : new_pos.neighbor(DOWN);
		jump_counter--;
		if (jump_counter == 0) jumping = false;
	}
	else {
		if (board->getChar(pos.neighbor(DOWN)) == ' ') {  // fall
			fall_counter++;
			new_pos = pos.neighbor(DOWN);
		}
		else {
			new_pos = pos.neighbor(dir);
		}
	}

	char new_tile = board->getChar(new_pos);

	if (new_tile != ch_ladder) {
		if (climbing) {
			climbing = false;
			dir = STAY;
		}
		if (new_tile != ' ' && new_tile != ch_pauline && new_tile != ch_dk) {
			new_pos = pos; // mario is not allowed to talk into floors or walls
		}
	}

	pos = new_pos;
	return true;
}

void Mario::reset()
{
	pos = board->startingPoint();
	dir = STAY;
	fall_counter = 0;
	jump_counter = 0;
	jumping = false;
}
