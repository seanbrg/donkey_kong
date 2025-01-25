#include <iostream>
#include "utils.h"
#include <Windows.h>
#include <filesystem>
#include <vector>


namespace utils {

	void gotoxy(int x, int y) {
		std::cout.flush();
		COORD coord; // Create a COORD structure 
		coord.X = x; // Set the X coordinate 
		coord.Y = y; // Set the Y coordinate 
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // Move the cursor 
	}

	void ShowConsoleCursor(bool showFlag) {
		HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO     cursorInfo;
		GetConsoleCursorInfo(out, &cursorInfo);
		cursorInfo.bVisible = showFlag; // set the cursor visibility
		SetConsoleCursorInfo(out, &cursorInfo);
	}

	void changeColor(char type)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		Color color;
		switch (type) {
		case ch_mario:
		case ch_dead_mario:
		case ch_hammer_dropped: // or right
		case ch_hammer_left:
		case ch_hammer_animation1:
		case ch_hammer_animation2:
		case 'l': // for label
			color = Color::BRIGHT_YELLOW;
			break;
		case ch_floor_flat:
		case ch_floor_left:
		case ch_floor_right:
			color = Color::BRIGHT_RED;
			break;
		case ch_ladder:
			color = Color::BRIGHT_BLUE;
			break;
		case ch_pauline:
			color = Color::PINK;
			break;
		case ch_explosion:
		case ch_dk:
			color = Color::ORANGE;
			break;
		case ch_ghost:
		case 'e': // easy (for the menu)
			color = Color::GREEN;
			break;
		case 'h': // hard (for the menu)
			color = Color::RED;
			break;
		default:
			color = Color::WHITE;
		}
		SetConsoleTextAttribute(hConsole, (short)color);
	}

	void resizeConsole()
	{
		HWND console = GetConsoleWindow();
		RECT r;
		GetWindowRect(console, &r); //stores the console's current dimensions
		MoveWindow(console, r.left, r.top, 80, 25, TRUE); // 80 width, 25 height
	}

	void findFiles(std::vector<std::string>& fileNames)
	{
		// Iterate through files in the directory
		for (const auto& entry : std::filesystem::directory_iterator(".")) {
			if (entry.is_regular_file()) {
				std::string filename = entry.path().filename().string();

				// Check if the filename matches the desired pattern
				if (filename.starts_with("dkong_") && filename.ends_with(".screen")) {
					fileNames.push_back(filename);
				}
			}
		}
		if (!fileNames.empty()) { // lexicographic sort
			std::sort(fileNames.begin(), fileNames.end());
		}
		else {
			std::cout << "ERROR: No valid files found.";
			Sleep(1000);
		}
	}
}