#pragma once
#include <iostream>


class Menu {
    int difficulty = 2; // game difficulty - 1 to 3
    bool colors = true;

public:    

    /**
     * displays the main menu leading to all other menus.
     */
    void display();

    /**
     * starts the game with the current settings.
     */
    void startGame();
    
    /**
     * displays and handles game settings options,
     * allowing the user to change the difficulty and toggle color mode.
     */
    void settingsMenu();
    
    /**
    * presents the game instructions and controls to the user.
    */
    void instructionsMenu() const;
    
    /**
     * displays an exit message and exits the game.
     */
    void exitMenu() const;
};


