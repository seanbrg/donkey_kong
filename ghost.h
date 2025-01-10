#pragma once
#include "utils.h"
#include "Point.h"
#include <list>
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
    Board* pBoard;

    static constexpr double SAME_DIR_PROB = 0.95;

public:
    /**
    * Constructor to initialize a ghost with position, direction, and board reference.
    * @param _pos: Initial position of the ghost.
    * @param _dir: Initial direction of the ghost.
    * @param _board: Pointer to the game board.
    */
    Ghost(const Point& _pos, Key _dir, Board* _board)
        : pos(_pos), dir(_dir), pBoard(_board) {}

    /**
     * Moves the ghost 
     */
    void move(const std::list<Ghost>& allGhosts);

    /**
     * Draws the ghost on the board.
     */
    void draw(char ch = ch_ghost) const;

    /**
     * Erases the ghost from the board.
     */
    void erase() const;

    /**
     * Gets the current position of the ghost.
     */
    Point getPos() const { return pos; }

    /**
     * Sets the direction of the ghost.
     */
    void setDirection(Key newDir) { dir = newDir; }
};