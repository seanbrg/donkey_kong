#include <Windows.h>
#include <iostream>
#include <conio.h> // for keyboard control

#include "utils.h"
#include "menu.h"

int main(int argc, char** argv) {
	resizeConsole();

	bool is_save = argc > 1 && std::string(argv[1]) == "-save";
	bool is_load = argc > 1 && std::string(argv[1]) == "-load";
	bool is_silent = is_load && argc > 2 && std::string(argv[2]) == "-silent";

	if (!is_load) {
		Menu menu(is_save);
		menu.display();
	}
	else {

	}
}