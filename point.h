#pragma once
#include "utils.h"

using namespace keys;

class Point {
	int x, y;

public:
	Point(int _x, int _y) : x(_x), y(_y) {}
	Point() = default;

	int getX() const { return x; }
	int getY() const { return y; }
	Point neighbor(Key dir);

	bool operator==(const Point& other) const {
		return x == other.x && y == other.y;
	}
};
