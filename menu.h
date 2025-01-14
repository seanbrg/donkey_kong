#pragma once
#include <iostream>
#include <vector>

class Menu {
    std::vector<std::string> fileNames;

    bool manual_files = false;
    int difficulty = 2; // game difficulty - 1 to 3
    bool colors = true;
    int current_menu = 0;   // 0 = main menu
                            // 1 = start game
                            // 2 = settings
                            // 8 = instructions
                            // 9 = exit

public:    

    /**
     * runs the menu logic by displaying the current menu.
     */
    void display();

    /**
     * starts the game with the current settings.
     */
    void startGame();
    
    /**
     * displays the main menu which leads to all other menus.
     */
    void mainMenu();

    void fileInputMenu();

    /**
     * displays and handles game settings options,
     * allowing the user to change the difficulty and toggle color mode.
     */
    void settingsMenu();
    
    /**
    * presents the game instructions and controls to the user.
    */
    void instructionsMenu();


    void findFiles();
};


