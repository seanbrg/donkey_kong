#pragma once
#include <iostream>
#include <vector>
#include "point.h"
#include "utils.h"

class Stage
{
	struct Floor
	{
		Point start; // leftmost point
		char type; // '<' '>' or '='
		int len; // length
	};

	Point start = { 4 , 22 };
	std::vector<Floor> floors;
	std::vector<Point> ladders;
	Stage* next = nullptr;

public:
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
	Point startingPoint() { return start; }
};

