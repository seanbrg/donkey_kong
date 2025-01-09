#include "hammer.h"

void Hammer::draw(char ch) const
{
	if (equipped) {
		Point equipped_pos = mario->getNext();
		if (board->getChar(equipped_pos) == ch_blank)
			board->drawChar(ch, equipped_pos);
	}
	else {
		board->drawChar(ch, pos);
	}
}
