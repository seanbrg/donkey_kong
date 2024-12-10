#pragma once
#include <iostream>

#include "utils.h"


class Floor
{
	Point start;
	char type;
	int len;
public:
	Floor(Point _start=Point(0, 0), char _type=ch_floor_flat, int _len=0) : start(_start), type(_type), len(_len) {}
	Point getStart() { return start; }
	char getType() { return type; }
	int getLen() { return len; }
};

