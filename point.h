#pragma once

class Point {
	int x, y;
public:
	Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}

	int getX() const { return x; }
	int getY() const { return y; }
	Point down() { return Point(x, y + 1); }
	Point left() { return Point(x - 1, y); }
	Point right() { return Point(x + 1, y); }
	Point up() { return Point(x, y - 1); }
};
