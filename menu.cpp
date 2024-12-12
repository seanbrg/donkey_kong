#include "menu.h"
#include "game.h"

#include <Windows.h> 

void Menu::handleStartGame() { 
    Game game;
    game.run();  
}

void Menu::handlePresentInstructions() {
    system("cls");
    std::cout << "Instructions and Keys:\n\n";
    std::cout << "Goal of the Game:\n\n";
    std::cout << "Donkey Kong is throwing barrels! Avoid them as you climb your way to the top.\n";
    std::cout << "Your objective is to reach Princess Pauline and rescue her to win the stage.\n\n";
    std::cout << "******************************************************************************\n\n";
    std::cout << "Keys to Move, Climb, and Jump:\n\n";
    std::cout << "1. Press 'a' to move left.\n";
    std::cout << "2. Press 'd' to move right.\n";
    std::cout << "3. Press 'w' to jump or climb ladders.\n";
    std::cout << "4. Press 'x' to go down or descend ladders.\n";
    std::cout << "5. Press 's' to stay in place.\n";

    std::cout << "\nPress any key to return to the menu";
    _getch();   
}


void Menu::handleExit() {
    std::cout << "exit...\n"; //?
}


char Menu::handleInputKey() {
    
    return _getch(); 
}


void Menu::displayMenu() {
    char choice = '\0';

    while (choice != '9') {
        system("cls");  

        
        std::string menu = "  _____    ____   _   _  _  ____     __  _  __ ____   _   _   _____         \n"
                           " |  __ \\  / __ \\ | \\ | || |/ /\\ \\   / / | |/ // __ \\ | \\ | | / ____| \n"
                           " | |  | || |  | ||  \\| || ' /  \\ \\_/ /  | ' /| |  | ||  \\| || |  __     \n"
                           " | |  | || |  | || . ` ||  <    \\   /   |  < | |  | || . ` || | |_ |       \n"
                           " | |__| || |__| || |\\  || . \\    | |    | . \\| |__| || |\\  || |__| |    \n"
                           " |_____/  \\____/ |_| \\_||_|\\_\\   |_|    |_|\_\\\\____/ |_| \\_| \\_____|\n"
                           "                                                                            \n"
                           "---------------------------------------------------------------------       \n"
                           "                                                                            \n"
                           "(1) Start Game                                                              \n"
                           "(8) Present Instructions and Keys                                           \n"
                           "(9) Exit                                                                    \n"
                           "                                                                            \n"
                           "                                                                            \n"
                           "                                                                            \n"
                           "                                                                            \n";

        std::cout << menu;

        
        std::cout << "\n\nEnter your choice: ";

        choice = handleInputKey();

        switch (choice) {
        case '1':
            handleStartGame();
            break;
        case '8':
            handlePresentInstructions();
            break;
        case '9':
            handleExit();
            break;
        default:
            std::cout << "\nInvalid choice. Try again.\n";
            _getch(); 
            break;
        }
    }
}