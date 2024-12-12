#include "point.h"

Point Point::neighbor(Key dir)
{
	switch (dir) {
	case(DOWN):
		return Point(x, y + 1);
	case (LEFT): 
		return Point(x - 1, y);
	case(RIGHT):
		return Point(x + 1, y);
	case(UP):
		return Point(x, y - 1);
	}
	return Point(0, 0);
}
