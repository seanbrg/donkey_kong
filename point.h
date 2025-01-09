#pragma once
#include "utils.h"

using namespace keys;

/**
 * represents a 2d point with x and y coordinates.
 */
class Point {
	int x, y;

public:

	/**
	 * constructs a point with given x and y coordinates.
	 * @param _x: the x coordinate of the point.
	 * @param _y: the y coordinate of the point.
	 */
	Point(int _x, int _y) : x(_x), y(_y) {}

	/**
	 * default constructor for empty point
	 */
	Point() = default;

	/**
	 * uses the '==' operator to compare two points by their x and y coordinates.
	 * @param other: the other point being compares.
	 * @return true if the points are equal, false otherwise.
	 */
	bool operator==(const Point& other) const {
		return x == other.x && y == other.y;
	}

	/**
	 * @return the x coordinate
	 */
	int getX() const { return x; }
	
	/**
	 * @return the y coordinate
	 */
	int getY() const { return y; }
	
	/**
	 * calculates the neighboring point in the specified direction.
	 * @param dir: the direction from the point (given as key).
	 * @return a new point that is next to this point in the given direction.
	 */
	Point neighbor(Key dir) const;
};
