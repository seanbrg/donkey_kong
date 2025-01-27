#include "hammer.h"

using namespace utils;

void Hammer::unequip()
{
	equipped = false;
	hitting = false;
	key_hit = false;
	pos = board->getHammer();
}

void Hammer::hit()
{
	if (equipped) {
		pos = mario->getNext();
		char next_char = board->getChar(pos);
		if (key_hit) {
			hit_pos = pos.neighbor(mario->getXaxisDir());
			char hit_char = board->getChar(hit_pos);
			if (next_char == ch_blank || next_char == ch_ladder) {
				draw(pos, ch_hammer_animation1);
				if (hit_char == ch_blank || hit_char == ch_ladder)
					draw(hit_pos, ch_hammer_animation2);
			}
			key_hit = false;
			hitting = true;
		}
	}
}

void Hammer::draw(Point draw_pos, char ch) const
{
	if (equipped) {
		if (key_hit) {
			board->drawChar(ch, draw_pos);
		}
		else if (!hitting) {
			Key facing = mario->getXaxisDir();
			Point next_pos = mario->getPos().neighbor(facing);
			char ch_hold = (facing == Key::LEFT) ? ch_hammer_left : ch_hammer_right;
			char next_char = board->getChar(next_pos);
			if (next_char == ch_blank || next_char == ch_ladder) {
				board->drawChar(ch_hold, next_pos);
			}
		}
	}
	else board->drawChar(ch_hammer_dropped, pos);
}

void Hammer::erase()
{
	if (hitting) {
		board->restoreChar(hit_pos);
		hitting = false;
	}
	if (equipped) {
		board->restoreChar(mario->getPos().neighbor(Key::LEFT));
		board->restoreChar(mario->getPos().neighbor(Key::RIGHT));
	}
	board->restoreChar(pos);
}