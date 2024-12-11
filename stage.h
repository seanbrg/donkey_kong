#pragma once
#include <iostream>
#include <vector>
#include "point.h"
#include "floor.h"
#include "utils.h"

class Stage
{
	Point start = { 4 , 22 };
	std::vector<Floor> floors; // floor class is unnecessary, use struct instead
	std::vector<Point> ladders;
	Stage* next = nullptr;

public:
	void addFloor(const Floor _floor) {
		floors.push_back(_floor);
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

