#pragma once
#include <iostream>
#include <vector>

#include "ladder.h"
#include "floor.h"
#include "utils.h"

class Stage
{
	std::vector<Floor> floors;
	std::vector<Ladder> ladders;
	Stage* next = nullptr;

public:
	void addFloor(const Floor& _floor) {
		floors.push_back(_floor);
	}
	void addLadder(const Ladder& _ladder) {
		ladders.push_back(_ladder);
	}
	void addNextStage(Stage*_next) {
		next = _next;
	}
	void load(char board[MAX_Y][MAX_X + 1]);
	Stage* getNext() { return next; }
};

