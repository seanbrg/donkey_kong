#pragma once
#include "utils.h"
#include "floor.h"

class Board {
	static constexpr int MIN_X = 5;
	static constexpr int MIN_Y = 5;
	static constexpr int MAX_X = 80;
	static constexpr int MAX_Y = 25;
	static constexpr int NUM_FLOORS = 1;
	static constexpr int NUM_LADDERS = 10;

	Floor* floors = nullptr;

	// TODO: function that automatically prints originalBoard using its dimensions
	// TODO: function that automatically prints each floor, and define all floors somewhere

	const char* originalBoard[MAX_Y] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		  "Q                                                                              Q", // 1
		  "Q                                                                              Q", // 2
		  "Q                                                                              Q", // 3
		  "Q                                                                              Q", // 4
		  "Q                                                                              Q", // 5
		  "Q                                                                              Q", // 6
		  "Q                                                                              Q", // 7
		  "Q                                                                              Q", // 8
		  "Q                                                                              Q", // 9
		  "Q                                                                              Q", // 10
		  "Q                                                                              Q", // 11
		  "Q                                                                              Q", // 12
		  "Q                                                                              Q", // 13
		  "Q                                                                              Q", // 14
		  "Q                                                                              Q", // 15
		  "Q                                                                              Q", // 16
		  "Q                                                                              Q", // 17
		  "Q                                                                              Q", // 18
		  "Q                                                                              Q", // 19
		  "Q                                                                              Q", // 20
		  "Q                                                                              Q", // 21
		  "Q                                                                              Q", // 22
		  "Q                                                                              Q", // 23
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"  // 24
	};
	char currentBoard[MAX_Y][MAX_X + 1]; // +1 for null terminator
public:
	Board();
	~Board();
	void reset() { Board(); }
	void print() const;
	char getChar(int x, int y) const {
		return currentBoard[y][x];
	}
};

