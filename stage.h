#pragma once
#include <iostream>
#include <vector>
#include "point.h"
#include "utils.h"

class Stage
{
	struct Floor // inner struct for saving floors...
	{
		Point start; // leftmost point
		char type; // '<' '>' or '='
		int len; // length
	};

	Point start_pos;
	Point win_pos;
	Point dk_pos;
	std::vector<Floor> floors;
	std::vector<Point> ladders;
	Stage* next = nullptr;

public:
	Stage(Point _start, Point _win, Point _dk) : start_pos(_start), win_pos(_win), dk_pos(_dk) {}
	Stage() = default;

	void addFloor(Point _start, char _type, int _len) {
		floors.push_back({ _start, _type, _len });
	}
	void addLadder(const Point _ladder) {
		ladders.push_back(_ladder);
	}
	void addNextStage(Stage* _next) {
		next = _next;
	}
	void load(char board[MAX_Y][MAX_X + 1]);
	Stage* getNext() { return next; }
	Point startingPoint() const { return start_pos; }
	Point winPoint() const { return win_pos; }
	Point dkPoint() const { return dk_pos; }
};

