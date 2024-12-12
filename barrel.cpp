#include "barrel.h"

void Barrel::move() // return if alive
{
	Point new_pos;

	switch (pBoard->getChar(pos.neighbor(DOWN))) {
	case ch_floor_left:
		dir = LEFT;
		break;
	case ch_floor_right:
		dir = RIGHT;
		break;
	}

	if (pBoard->getChar(pos.neighbor(DOWN)) != ' ' && fall_counter > 0) {
		if (fall_counter >= 8) {
			exploding = true;
			active = false; // remove later when explosions are added
			return;
		}
		fall_counter = 0;
	}

	
	if (pBoard->getChar(pos.neighbor(DOWN)) == ' ') {  // fall
		fall_counter++;
		new_pos = pos.neighbor(DOWN);
	}
	else {
		new_pos = pos.neighbor(dir);
	}

	char new_tile = pBoard->getChar(new_pos);

	if (new_tile == ch_border)
		active = false;

	pos = new_pos;
}
