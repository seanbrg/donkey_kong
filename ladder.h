#pragma once
#include <iostream>

#include "utils.h"


class Ladder
{
	Point start;
	char ch = 'H';
public:
	Ladder(Point _start = Point(0,0)) : start(_start) {}

	Point getStart() { return start; }
	char getChar() { return ch; }
};
