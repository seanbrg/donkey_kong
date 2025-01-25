#pragma once
#include <iostream>
#include <vector>

class Menu {
    std::vector<std::string> fileNames;

    enum class MenuType { MAIN, START, SETTINGS, INPUT, INSTRUCTIONS, EXIT };

    bool save_mode;
    bool manual_files = false;
    int difficulty = 2; // game difficulty - 1 to 3
    bool colors = true;
    MenuType current_menu = MenuType::MAIN;

public:    

    /*
    * constructor
    * @param _save: boolean parameter indicating save mode
    */
    Menu(bool _save=false) : save_mode(_save) {}

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

    /*
    * displays and handles the file selection menu.
    */
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
};


