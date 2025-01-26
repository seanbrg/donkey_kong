#include "donkeykong.h"
#include "entity.h"
#include "barrel.h"

using namespace utils;


void DonkeyKong::spawnBarrels(std::list<EntityPtr>& entities)
{
	if (twice_mode) {
		EntityPtr barrel_left = (EntityPtr)new Barrel(pos, Key::LEFT, pBoard);
		EntityPtr barrel_right = (EntityPtr)new Barrel(pos, Key::RIGHT, pBoard);

		entities.push_back(barrel_left);
		entities.push_back(barrel_right);
	}
	else { // default
		barrels_dir = (barrels_dir == Key::LEFT) ? Key::RIGHT : Key::LEFT;
		EntityPtr barrel_next = (EntityPtr)new Barrel(pos, barrels_dir, pBoard);

		entities.push_back(barrel_next);
	}
}
