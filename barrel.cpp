#include "barrel.h"
#include "board.h"

using namespace utils;

void Barrel::move(std::list<EntityPtr>& allEntities)
{
	if (explode) {
		active = false;
	}
	else {
		Board* pBoard = Entity::getBoard();
		Point pos = Entity::getPos();
		Key dir = Entity::getDir();
		Point new_pos;
		char floor = pBoard->getChar(pos.neighbor(Key::DOWN));

		switch (floor) {
		case ch_floor_left:
			dir = Key::LEFT;
			break;
		case ch_floor_right:
			dir = Key::RIGHT;
			break;
		}
		Entity::setDir(dir);

		if (floor == ' ') {  // fall
			fall_counter++;
			new_pos = pos.neighbor(Key::DOWN);
		}
		else {
			new_pos = pos.neighbor(dir);
		}

		char new_tile = pBoard->getChar(new_pos);

		if (new_tile == ch_border)
			active = false;

		if (floor != ' ' && fall_counter > 0) {
			if (fall_counter >= 8) {
				explode = true;
			}
			fall_counter = 0;
		}
		if (!explode) Entity::setPos(new_pos);
	}
}

void Barrel::drawExplosion() const
{
	Board* pBoard = Entity::getBoard();
	Point pos = Entity::getPos();

	for (int x = 0 - explosion_range; x <= explosion_range; x++) {
		for (int y = 0 - explosion_range; y <= 0; y++) {
			Point pos_explosion = { pos.getX() + x, pos.getY() + y };
			if (pBoard->getChar(pos_explosion) == ' ') {
				pBoard->drawChar(ch_explosion, pos_explosion);
			}
		}
	}
}
