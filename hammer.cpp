#include "hammer.h"

void Hammer::draw()
{
	if (equipped) {
		pos = mario->getNext();
		char next_char = board->getChar(pos);
		if (next_char == ch_blank || next_char == ch_ladder) {
			char ch = (mario->getXaxisDir() == LEFT) ? ch_hammer_left : ch_hammer_right;
			board->drawChar(ch, pos);
		}
	}
	else {
		board->drawChar(ch_hammer_dropped, pos);
	}
}

void Hammer::erase() const
{
	if (equipped)
		board->restoreChar(pos);
	else
		board->restoreChar(pos);
}
