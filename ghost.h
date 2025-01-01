#pragma once
#include "utils.h"
#include "Point.h"
#include <vector>
#include <random>

using namespace keys;

class Board;

/**
 * Represents a ghost in the game.
 */
class Ghost {
private:
    Point pos;      
    Key dir;       
    Board* board;        

public:
    /**
     * Constructor for the Ghost.
     * @param pos: Initial position of the ghost.
     * @param dir: Initial direction of the ghost.
     * @param b: Pointer to the board.
     */
    Ghost(Point _pos, Key _dir, Board* _b);

    /**
     * Moves the ghost 
     */
    void move();

    /**
     * Detects if the ghost collides with Mario 
     * @param marioPos: The position of Mario.
     * @return true if the ghost collides with Mario, false otherwise.
     */
    bool detectMario(Point marioPos);

    /**
     * Reverses the ghost's direction.
     */
    void reverseDirection();

    /**
     * Draws the ghost on the board at its current position.
     */
    void draw() const;
};
