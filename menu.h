#pragma once
#include <iostream>


class Menu {
    int difficulty = 2;
    bool colors = true;

public:    
    void startGame();
    void settingsMenu();
    void instructionsMenu() const;
    void exitMenu() const;
    void display();
};


