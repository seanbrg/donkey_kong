#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>
#include "menu.h"
#include "game.h"

void Menu::startGame() { 
    if (!manual_files || fileNames.empty())
        findFiles(fileNames);

    Game game(fileNames, colors, difficulty, save_mode);

    game.run();
    fileNames.clear();
    manual_files = false;
}

void Menu::display() {
    system("cls"); // clear screen

    while (current_menu != 9) {
        switch (current_menu) { // display the current menu
        case 1:
            startGame();
            current_menu = 0;
            break;
        case 2:
            settingsMenu();
            break;
        case 3:
            fileInputMenu();
            break;
        case 8:
            instructionsMenu();
            break;
        case 9: // exit
            break;
        default:
            mainMenu();
            break;
        }
    }

    gotoxy(0, 15);
    std::cout << "\nExiting game...                          \n"; // exit message
}

void Menu::settingsMenu()
{
    system("cls");

    if (colors)
        changeColor(ch_dk);
    std::cout << "Game Settings:\n\n";
    std::cout << "Currently the difficulty is set to ";
    switch (difficulty) { // print difficulty level
    case 1:
        if (colors)
            changeColor('e');
        std::cout << "Easy.\n";
        if (colors)
            changeColor(ch_dk);
        break;
    case 2:
        std::cout << "Normal.\n";
        break;
    case 3:
        if (colors)
            changeColor('h');
        std::cout << "Hard.\n";
        if (colors)
            changeColor(ch_dk);
        break;
    }
    std::cout << "This affects the game speed and the amount of barrels that will spawn.\n\n";

    if (colors)
        std::cout << "The game is currently in color mode.\n";
    else
        std::cout << "The game is currently in colorless mode.\n";

    std::cout << "******************************************************************************\n\n";
    std::string settings = 
        "Change Settings:\n\n"
        "(1) Change difficulty to Easy.\n"
        "(2) Change difficulty to Normal.\n"
        "(3) Change difficulty to Hard.\n"
        "(4) Switch color mode.\n"
        "(9) Return to the main menu.\n\n";

    if (colors)
        changeColor();
    std::cout << settings;

    char choice = _getch();

    switch (choice) { // handle changing settings through input
    case '1':
        difficulty = 1;
        break;
    case '2':
        difficulty = 2;
        break;
    case '3':
        difficulty = 3;
        break;
    case '4':
        colors = !colors;
        break;
    case '9':
        current_menu = 0; // return to main menu
        break;
    default:
        gotoxy(0, 14);
        std::cout << "\nInvalid choice. Please try again.\n";
        Sleep(800);
        gotoxy(0, 14);
        std::cout << "\n                                   \n";
        break;
    }
}

void Menu::instructionsMenu() {
    system("cls");

    std::string instructions = 
        "Instructions and Controls:\n\n"
        "Goal of the Game:\n"
        "Donkey Kong is throwing barrels! Avoid them as you climb your way to the top.\n"
        "Your objective is to reach Princess Pauline and rescue her to win the game.\n"
        "******************************************************************************\n\n";

    std::string controls = 
        "Important: Your language must be set to English for the keys to register.\n\n"
        "Movement keys:\n"
        "**************\n"
        " - Press 'a' to move left.\n"
        " - Press 'd' to move right.\n"
        " - Press 'w' to jump or climb ladders.\n"
        " - Press 'x' to descend ladders.\n"
        " - Press 's' to stay in place.\n"
        "\nAdditional keys:\n"
        "****************\n"
        " - Press 'p' to hit with a hammer.\n"
        " - Press 'ESC' to pause the game.\n"
        "\nPress any key to return to the main menu.\n";

    if (colors)
        changeColor(ch_dk);
    std::cout << instructions;

    if (colors)
        changeColor();
    std::cout << controls;

    _getch(); // await input to return to main menu
    current_menu = 0;
}

void Menu::mainMenu() {
    char choice = '\0';
    system("cls");  
    std::string header =
        "    ______ _____ _   _  _   __ _______   __  _   _______ _   _ _____           \n"
        "    |  _  \\  _  | \\ | || | / /|  ___\\ \\ / / | | / /  _  | \\ | |  __ \\    \n"
        "    | | | | | | |  \\| || |/ / | |__  \\ V /  | |/ /| | | |  \\| | |  \\/        \n"
        "    | | | | | | | . ` ||    \\ |  __|  \\ /   |    \\| | | | . ` | | __          \n"
        "    | |/ /\\ \\_/ / |\\  || |\\  \\| |___  | |   | |\\  \\ \\_/ / |\\  | |_\\ \\ \n"
        "    |___/  \\___/\\_| \\_/\\_| \\_/\\____/  \\_/   \\_| \\_/\\___/\\_| \\_/\\____/\n"
        "    -----------------------------------------------------------------            \n"
        "                                                                               \n";
    std::string menu =
        "(1) Start Game                                                                 \n"
        "(2) Game Settings (colors and difficulty)                                      \n"
        "(3) Manually load screen files                                                 \n"
        "(8) Instructions and Controls                                                  \n"
        "(9) Exit                                                                       \n";

    if (colors)
        changeColor(ch_dk);
    std::cout << header; // print header
    if (colors)
        changeColor();
    std::cout << menu; // print menu

    gotoxy(0, 15);
    std::cout << "\n\Awaiting input:                         \n";

    choice = _getch();

    while (choice != '1' && choice != '2' && choice != '3' && choice != '8' && choice != '9') { // wait for correct input
        gotoxy(0, 15);
        std::cout << "\nInvalid choice. Please try again.\n";
        choice = _getch();
    }
    current_menu = choice - '0'; // update menu
}

void Menu::fileInputMenu()
{
    system("cls");

    std::string instructions = 
                "Write screen file names here to load them as replacements of the default stages.\n"
                "Files must be of .screen format and each must contain a single game stage\n"
                "drawn with text, which must include all the necessary game elements.\n"
                "Please ensure that the files are in the game directory before input.\n"
                "********************************************************************************\n";

    if (colors) changeColor(ch_dk);
    std::cout << instructions;
    if (colors) changeColor();

    if (!fileNames.empty()) {
        std::cout << "\nCurrently loaded files:\n";
        for (auto file : fileNames)
            std::cout << file << std::endl;

        std::cout << "\nInput 'd' to cancel loaded files.\n";
    }
    std::cout << "\nWaiting for input (input 'x' to return to main menu):\n";

    std::string input;
    std::cin >> input;
    if (input == "x") {
        current_menu = 0;
    }
    else if (input == "d" && !fileNames.empty()) {
        fileNames.clear();
    }
    else {
        bool found = false;

        for (const auto& entry : std::filesystem::directory_iterator(".")) { // search file in local directory
            if (entry.is_regular_file()) {
                std::string filename = entry.path().filename().string();
                if (filename == input && filename.ends_with(".screen")) {
                    found = true;
                    manual_files = true;
                    fileNames.push_back(filename);
                    break;
                }
            }
        }
        if (!found) {
            std::cout << "File not found.";
            Sleep(800);
        }
    }
}