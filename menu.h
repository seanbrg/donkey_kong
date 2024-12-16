#pragma once
#include <iostream>


class Menu {
    int difficulty = 2;
    bool colors = false;
public:
    
    void handleStartGame();
    void handeOptions();
    void handlePresentInstructions();
    void handleExit();
    void displayMenu();
};


