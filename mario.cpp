#include "mario.h"
#include "utils.h"

void Mario::keyPressed(char key)
{
	switch (std::tolower(key)) {
	case((char)eKeys::LEFT):
		dir = { -1, 0 };
		break;
	case((char)eKeys::STAY):
		dir = { 0, 0 };
		break;
	case((char)eKeys::RIGHT):
		dir = { 1, 0 };
		break;
	case((char)eKeys::UP):
		if (pBoard->getChar(pos) == ch_ladder) {
			dir = { 0, -1 }; // start climbing up
			climbing = true;
		}
		else if (pBoard->getChar({ pos.x , pos.y + 1 }) != ' ') {
			jumps_remaining = 2; // start jumping
			jump_dir = dir;
			jumping = true;
		}
		break;
	case((char)eKeys::DOWN):
		if (pBoard->getChar({ pos.x , pos.y + 1 }) == ch_ladder) {
			dir = { 0, 1 }; // start climbing down
			climbing = true;
		}
		break;
	}
	
	return;
}

void Mario::move()
{
	Point new_pos;

	if (jumping) {
		if (jump_dir.x == 0 || jumps_remaining > 1) // jump in place or first stage of side jump
			jump_dir = { jump_dir.x, -1 };
		else jump_dir = { jump_dir.x, 1 }; // second stage of side jump

		jumps_remaining--;
		if (jumps_remaining == 0) jumping = false;
		new_pos = { pos.x + jump_dir.x, pos.y + jump_dir.y };
	}
	else {
		if (pBoard->getChar({ pos.x, pos.y + 1 }) == ' ') {
			falling = true;
			new_pos = { pos.x, pos.y + 1 }; // don't forget original dir, return to it later
		}
		else {
			if (falling) { // stop falling
				dir = { dir.x, 0 };
				falling = false;
			}
			new_pos = { pos.x + dir.x , pos.y + dir.y };
		}
	}
	char new_floor = pBoard->getChar(new_pos);

	if (new_floor != ch_ladder) {
		if (climbing) {
			climbing = false;
			dir = { 0, 0 };
		}
		if (new_floor != ' ') new_pos = pos;
	}
	pos = new_pos;
}