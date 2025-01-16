#pragma once
#include "utils.h"
#include "point.h"
#include "entity.h"

#include <list>
#include <random>


using namespace keys;

class Board;

/**
 * Represents a ghost in the game.
 */
class Ghost : public Entity {
private:
    static constexpr double SAME_DIR_PROB = 0.95;

public:
    /**
    * Constructor to initialize a ghost with position, direction, and board reference.
    * @param _pos: Initial position of the ghost.
    * @param _dir: Initial direction of the ghost.
    * @param _board: Pointer to the game board.
    */
    Ghost(Point _pos, Key _dir, Board* _board) : Entity(_pos, _dir, _board) {}

    /**
     * Moves the ghost 
     */
    void move(std::list<EntityPtr>& allEntities) override;

    /**
     * Draws the ghost on the board.
     */
    void draw(char ch = ch_ghost) const override { Entity::draw(ch_ghost); };
};