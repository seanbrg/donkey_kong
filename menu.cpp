#include "menu.h"
#include "game.h"

#include <Windows.h> 

void Menu::handleStartGame() { 
    Game game(colors, difficulty);
    game.run();  
}

void Menu::handeOptions()
{
    system("cls");
    std::cout << "Game Settings:\n\n";
    std::cout << "Currently the difficulty is set to ";
    switch (difficulty) {
    case 1:
        std::cout << "Easy.\n";
        break;
    case 2:
        std::cout << "Normal.\n";
        break;
    case 3:
        std::cout << "Hard.\n";
        break;
    }
    std::cout << "This affects the game speed and the amount of barrels that will spawn.\n\n";

    if (colors)
        std::cout << "The game is currently in color mode.\n\n";
    else
        std::cout << "The game is currently in colorless mode.\n\n";

    std::cout << "******************************************************************************\n\n";

    std::cout << "Change Settings:\n\n";
    std::cout << "(1) Change difficulty to Easy.\n";
    std::cout << "(2) Change difficulty to Normal.\n";
    std::cout << "(3) Change difficulty to Hard.\n";
    std::cout << "(5) Switch color mode.\n";
    std::cout << "(6) Return to the main menu.\n\n";

    char choice = _getch();

    switch (choice) {
    case '1':
        difficulty = 1;
        break;
    case '2':
        difficulty = 2;
        break;
    case '3':
        difficulty = 3;
        break;
    case '5':
        colors = !colors;
        break;
    case '6':
        break;
    default:
        gotoxy(0, 17);
        std::cout << "\nInvalid choice. Please try again.\n";
        Sleep(800);
        gotoxy(0, 16);
        std::cout << "\n                                   \n";
        break;
    }

    if (choice != '6')
        handeOptions();
}

void Menu::handlePresentInstructions() {
    system("cls");
    std::cout << "Instructions and Controls:\n\n";
    std::cout << "Goal of the Game:\n";
    std::cout << "Donkey Kong is throwing barrels! Avoid them as you climb your way to the top.\n";
    std::cout << "Your objective is to reach Princess Pauline and rescue her to win the game.\n";
    std::cout << "******************************************************************************\n\n";
    std::cout << "Important: Your language must be set to English for the keys to register.\n\n";
    std::cout << "Movement keys:\n" << "**************\n";
    std::cout << " - Press 'a' to move left.\n";
    std::cout << " - Press 'd' to move right.\n";
    std::cout << " - Press 'w' to jump or climb ladders.\n";
    std::cout << " - Press 'x' to descend ladders.\n";
    std::cout << " - Press 's' to stay in place.\n";
    std::cout << "\nAdditional keys:\n" << "****************\n";
    std::cout << " - Press 'ESC' to pause the game.\n";

    std::cout << "\nPress any key to return to the main menu.\n";
    _getch();   
}


void Menu::handleExit() {
    gotoxy(0, 15);
    std::cout << "\nExiting game...                          \n";
}

void Menu::displayMenu() {
    char choice = '\0';

    while (choice != '9') {
        system("cls");  

        
        std::string menu =
            "  ______ _____ _   _  _   __ _______   __  _   _______ _   _ _____             \n"
            "  |  _  \\  _  | \\ | || | / /|  ___\\ \\ / / | | / /  _  | \\ | |  __ \\      \n"
            "  | | | | | | |  \\| || |/ / | |__  \\ V /  | |/ /| | | |  \\| | |  \\/        \n"
            "  | | | | | | | . ` ||    \\ |  __|  \\ /   |    \\| | | | . ` | | __          \n"
            "  | |/ /\\ \\_/ / |\\  || |\\  \\| |___  | |   | |\\  \\ \\_/ / |\\  | |_\\ \\ \n"
            "  |___/  \\___/\\_| \\_/\\_| \\_/\\____/  \\_/   \\_| \\_/\\___/\\_| \\_/\\____/\n"
            "  -----------------------------------------------------------------            \n"
            "                                                                               \n"
            "(1) Start Game                                                                 \n"
            "(2) Game Settings (colors and difficulty)                                      \n"
            "(8) Instructions and Controls                                                  \n"
            "(9) Exit                                                                       \n";

        std::cout << menu;

        gotoxy(0, 15);
        std::cout << "\n\Awaiting input:                         \n";

        choice = _getch();

        switch (choice) {
        case '1':
            handleStartGame();
            break;
        case '2':
            handeOptions();
            break;
        case '8':
            handlePresentInstructions();
            break;
        case '9':
            handleExit();
            break;
        default:
            gotoxy(0, 15);
            std::cout << "\nInvalid choice. Please try again.\n";
            Sleep(800);
            break;
        }
    }
    
}