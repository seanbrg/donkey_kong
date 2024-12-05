#pragma once
#include <iostream>

#include "utils.h"


class Floor
{
	Point start;
	char type;
	int len;
public:
	Floor() : start(Point(0, 0)), type('='), len(0) {} // default constructor
	Floor(Point _start, char _type, int _len) : start(_start), type(_type), len(_len) {}
	
	// TODO: draw() and isOn()
	void draw();
	bool isOn(Point pos);
};

