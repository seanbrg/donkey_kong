#include "floor.h"
#include <iostream>

void Floor::draw()
{
	for (int i = 0; i < len; i++) {
		gotoxy(start.x + i, start.y);
		std::cout << type;
	}
}

bool Floor::isOn(Point pos)
{
	return (pos.y == start.y + 1 && start.x <= pos.x <= start.x + len);
}
