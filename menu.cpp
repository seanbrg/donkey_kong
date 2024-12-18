#include "menu.h"
#include "game.h"

void Menu::startGame() { 
    Game game(colors, difficulty);
    game.run();  
}

void Menu::settingsMenu()
{
    system("cls");

    if (colors)
        changeColor(ch_dk);
    std::cout << "Game Settings:\n\n";
    std::cout << "Currently the difficulty is set to ";
    switch (difficulty) {
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
        break;
    default:
        gotoxy(0, 14);
        std::cout << "\nInvalid choice. Please try again.\n";
        Sleep(800);
        gotoxy(0, 14);
        std::cout << "\n                                   \n";
        break;
    }

    if (choice != '9')
        settingsMenu();
}

void Menu::instructionsMenu() const {
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
        " - Press 'ESC' to pause the game.\n";

    if (colors)
        changeColor(ch_dk);
    std::cout << instructions;

    if (colors)
        changeColor();
    std::cout << controls;

    _getch(); // await input to return to main menu
}


void Menu::exitMenu() const {
    gotoxy(0, 15);
    std::cout << "\nExiting game...                          \n";
}

void Menu::display() {
    char choice = '\0';

    while (choice != '9') {
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
            "(8) Instructions and Controls                                                  \n"
            "(9) Exit                                                                       \n";

        if (colors)
            changeColor(ch_dk);
        std::cout << header;
        if (colors)
            changeColor();
        std::cout << menu;

        gotoxy(0, 15);
        std::cout << "\n\Awaiting input:                         \n";

        choice = _getch();

        switch (choice) { // handle choosing next menu through input
        case '1':
            startGame();
            break;
        case '2':
            settingsMenu();
            break;
        case '8':
            instructionsMenu();
            break;
        case '9':
            exitMenu();
            break;
        default:
            gotoxy(0, 15);
            std::cout << "\nInvalid choice. Please try again.\n";
            Sleep(800);
            break;
        }
    }
    
}