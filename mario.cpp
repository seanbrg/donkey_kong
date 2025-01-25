#include "mario.h"
#include "utils.h"

using namespace utils;

void Mario::keyPressed(Key key)
{
	if (key == Key::UP && board->getChar(pos) == ch_ladder) {
		climbing = true; // climb up
		dir = key;
	}
	else if (key == Key::DOWN && board->getChar(pos.neighbor(Key::DOWN)) == ch_ladder) {
		climbing = true; // climb down
		dir = key;
	}
	else if (key == Key::UP && board->getChar(pos.neighbor(Key::DOWN)) != ' ') {
		jump_counter = 2; // jump
		jump_dir = (dir == Key::STAY) ? Key::UP : dir; // set direction of jump
		jumping = true;
	}
	else if (key == Key::RIGHT || key == Key::LEFT || key == Key::STAY) {
		dir = (!climbing) ? key : Key::STAY;
		if (dir == Key::LEFT || dir == Key::RIGHT)
			x_axis_dir = dir;
	}
}

bool Mario::move()
{
	Point new_pos;

	if (board->getChar(pos.neighbor(Key::DOWN)) != ' ' && fall_counter > 0) {
		if (fall_counter >= mario_max_fall_height)
			return false;
		fall_counter = 0;
	}

	if (jump_counter > 0) { // jumping logic
		new_pos = pos.neighbor(jump_dir);
		if (jump_dir != Key::UP) // jump counter iterates from 2 to 0 to calculate jump positions
			new_pos = (jump_counter == 2) ? new_pos.neighbor(Key::UP) : new_pos.neighbor(Key::DOWN);
		jump_counter--;
	}
	else {
		if (board->getChar(pos.neighbor(Key::DOWN)) == ' ') {  // fall
			fall_counter++;
			new_pos = pos.neighbor(Key::DOWN);
		}
		else {
			jumping = false;
			new_pos = pos.neighbor(dir);
		}
	}

	char new_tile = board->getChar(new_pos);

	if (new_tile != ch_ladder) {
		if (climbing) {
			climbing = false;
			dir = Key::STAY;
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
	pos = board->getStart();
	dir = Key::STAY;
	fall_counter = 0;
	jump_counter = 0;
	jumping = false;
}
