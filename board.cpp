#include <cstring>
#include <iostream>
#include <fstream>
#include "board.h"
#include "utils.h"
#include "entity.h"
#include "ghost.h"

using namespace utils;

char Board::getChar(const Point& pos) const {
	return currentBoard[pos.getY()][pos.getX()];
}

void Board::drawChar(char c, const Point& pos) const {
	gotoxy(pos.getX() + MIN_X, pos.getY() + MIN_Y);
	if (colors)
		changeColor(c);

	std::cout << c;
}

void Board::restoreChar(const Point& pos) const {
	int x = pos.getX();
	int y = pos.getY();

	gotoxy(x + MIN_X, y + MIN_Y);

	//get char of current pos
	char current_char = currentBoard[y][x];

	if (colors)
		changeColor(current_char);

	std::cout << current_char;
}

void Board::restoreBoardExplosion(const Point& explosion) const
{
	for (int x = 0 - explosion_range; x <= explosion_range; x++) {
		for (int y = 0 - explosion_range; y <= explosion_range; y++) {
			Point former_explosion = { explosion.getX() + x, explosion.getY() + y };
			restoreChar(former_explosion);
		}
	}
}

void Board::reset()
{
	for (int y = 0; y < MAX_Y; y++) {
		memcpy(currentBoard[y], originalStageBoard[y], MAX_X + 1);
	}
}

void Board::print() const {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 

	for (int i = 0; i < MAX_Y; i++) {
		gotoxy(MIN_X, MIN_Y + i);  

		for (int j = 0; j < MAX_X + 1; j++) {
			char current_char = currentBoard[i][j];
			if (colors)
				changeColor(current_char);

			std::cout << current_char;
		}

		if (i < MAX_Y - 1)
			std::cout << '\n';
	}
	SetConsoleTextAttribute(hConsole, ch_blank);
}

bool Board::load(const std::string& fileName)
{
	std::ifstream screen_file(fileName);
	if (!screen_file.is_open()) {
		std::cerr << "Error: Unable to open the file: " << fileName << std::endl;
		std::cout << "Press anything to return to main menu.";
		_getch();
		return false;
	}
	
	ghost_locs.clear();
	// following flags are for checking if something has appeared:
	bool flag_start = false;	
	bool flag_pauline = false;
	bool flag_dk = false;
	bool flag_legend = false;
	bool flag_hammer = false;
	bool flag_once = true;	// false if anything appeared more than once
	bool out_of_bounds = false;

	int curr_row = 0;
	int curr_col = 0;
	char c;

	while (!screen_file.get(c).eof() && curr_row <= MAX_Y) {
		if (c == '\n') {
			if (curr_col < MAX_X) { // add spaces for missing columns
				#pragma warning(suppress : 4996) // to allow strcpy
				strcpy(originalStageBoard[curr_row] + curr_col, std::string(MAX_X - curr_col, ' ').c_str());
			}
			++curr_row;
			curr_col = 0;
			continue;
		}
		if (curr_col <= MAX_X) {
			Point position(curr_col, curr_row);

			switch (c) {
			case ch_mario:
				if (position.inBounds()) {
					if (!flag_start) flag_start = true;
					else flag_once = false;
					start_pos = position;
					c = ' ';
				}
				else out_of_bounds = true;
				break;
			case ch_hammer_dropped:
				if (position.inBounds()) {
					if (!flag_hammer) flag_hammer = true;
					else flag_once = false;
					hammer_pos = position;
					c = ' ';
				}
				else out_of_bounds = true;
				break;
			case ch_legend_symbol:
				if (position.inBounds()) {
					if (!flag_legend) flag_legend = true;
					else flag_once = false;
					legend_pos = position;
					c = ' ';
				}
				else out_of_bounds = true;
				break;
			case ch_dk:
				if (position.inBounds()) {
					if (!flag_dk) flag_dk = true;
					else flag_once = false;
					dk_pos = position;
				}
				else out_of_bounds = true;
				break;
			case ch_pauline:
				if (position.inBounds()) {
					if (!flag_pauline) flag_pauline = true;
					else flag_once = false;
					pauline_pos = position;
				}
				else out_of_bounds = true;
				break;
			case ch_ghost:
				ghost_locs.push_back(position);
				c = ' ';
				break;
			case ch_big_ghost:
				big_ghost_locs.push_back(position);
				c = ' ';
				break;
			case ch_ladder:
			case ch_floor_flat:
			case ch_floor_left:
			case ch_floor_right:
				break;
			default: // including 'Q', to not draw any border from the file, as we draw our own borders
				c = ' ';
				break;
			}
			originalStageBoard[curr_row][curr_col] = c;
			++curr_col;
		}
	}

	if (!flag_pauline || !flag_dk || !flag_start || !flag_once || out_of_bounds) {
		std::cerr << "Error: file " << fileName << " is invalid: ";
		if (!flag_pauline) std::cout << std::endl << "No valid Pauline symbol found in screen file";
		if (!flag_dk) std::cout << std::endl << "No valid Donkey Kong symbol found in screen file";
		if (!flag_start) std::cout << std::endl << "No valid Mario symbol found in screen file";
		if (!flag_once) std::cout << std::endl << "Essential game element exists more than once in file";
		if (out_of_bounds) std::cout << std::endl << "Essential game element is in an invalid position";
		std::cout << std::endl << "Press anything to continue to next file or return to main menu.";
		_getch();
		return false;
	}
	else {
		int last_row = (curr_row <= MAX_Y - 1 ? curr_row : MAX_Y - 1);

		// add a frame of 'Q' even if file didn't have one
		#pragma warning(suppress : 4996) // to allow strcpy
		strcpy(originalStageBoard[0], std::string(MAX_X, ch_border).c_str()); // first row

		#pragma warning(suppress : 4996) // to allow strcpy
		strcpy(originalStageBoard[last_row], std::string(MAX_X, ch_border).c_str()); // last row

		// first and last columns
		for (int row = 0; row <= last_row; ++row) {
			originalStageBoard[row][0] = ch_border;
			originalStageBoard[row][MAX_X] = ch_border;
		}

		hammer_in_board = flag_hammer;
		if (!flag_legend) legend_pos = Point(2, 1); // fix missing L

		return true;
	}
}
