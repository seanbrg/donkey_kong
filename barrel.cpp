#include "barrel.h"

void Barrel::move() // return if alive
{
	if (explode) {
		active = false;
	}
	else {

		Point new_pos;

		switch (pBoard->getChar(pos.neighbor(DOWN))) {
		case ch_floor_left:
			dir = LEFT;
			break;
		case ch_floor_right:
			dir = RIGHT;
			break;
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

		if (pBoard->getChar(pos.neighbor(DOWN)) != ' ' && fall_counter > 0) {
			if (fall_counter >= 8) {
				explode = true;
			}
			fall_counter = 0;
		}
	}
}

void Barrel::drawExplosion() const
{
	for (int x = 0 - explosion_range; x <= explosion_range; x++) {
		for (int y = 0 - explosion_range; y <= explosion_range; y++) {
			int explosion_x = pos.getX() + x;
			int explosion_y = pos.getY() + y;
			if (pBoard->getChar({ explosion_x, explosion_y }) == ' ') {
				gotoxy(explosion_x + MIN_X, explosion_y + MIN_Y);
				std::cout << ch_explosion;
			}
		}
	}
}
