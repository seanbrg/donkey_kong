#include "hammer.h"

bool Hammer::draw()
{
	if (equipped) {

		pos = mario->getNext();
		char next_char = board->getChar(pos);
		if (key_hit) {
			hit = pos.neighbor(mario->getXaxisDir());
			char hit_char = board->getChar(hit);
			if (next_char == ch_blank || next_char == ch_ladder) {
				board->drawChar(ch_hammer_animation1, pos);
				if (hit_char == ch_blank || hit_char == ch_ladder)
					board->drawChar(ch_hammer_animation2, hit);
			}
			key_hit = false;
			hitting = true;
		}
		else if (next_char == ch_blank || next_char == ch_ladder) {
			char ch = (mario->getXaxisDir() == LEFT) ? ch_hammer_left : ch_hammer_right;
			board->drawChar(ch, pos);
		}
	}
	else {
		board->drawChar(ch_hammer_dropped, pos);
	}

	return hitting;
}

void Hammer::erase()
{
	if (hitting) {
		hitting = false;
		board->restoreChar(hit);
	}

	if (equipped)
		board->restoreChar(pos);
	else
		board->restoreChar(pos);
}