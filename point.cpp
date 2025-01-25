#include "point.h"

Point Point::neighbor(utils::Key dir) const
{
	switch (dir) {
	case utils::Key::LEFT:
		return Point(x - 1, y);
	case utils::Key::RIGHT:
		return Point(x + 1, y);
	case utils::Key::UP:
		return Point(x, y - 1);
	case utils::Key::DOWN:
		return Point(x, y + 1);
	default:
		return *this;
	}
}
