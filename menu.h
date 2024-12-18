#pragma once
#include <iostream>


class Menu {
    int difficulty = 2;
    bool colors = true;
public:
    
    void handleStartGame();
    void handeOptions();
    void handlePresentInstructions();
    void handleExit();
    void displayMenu();
};


