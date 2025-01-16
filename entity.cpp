#include "entity.h"
#include "board.h"

void Entity::draw(char ch) const {
	pBoard->drawChar(ch, pos);
}

void Entity::erase() const {
	pBoard->restoreChar(pos);
}