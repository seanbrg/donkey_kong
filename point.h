#pragma once
#include "utils.h"
using namespace keys;

class Point {
	int x, y;
public:
	Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}

	int getX() const { return x; }
	int getY() const { return y; }
	Point neighbor(Key dir);
};
