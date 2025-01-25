#pragma once
#include "utils.h"
#include "point.h"
#include "entity.h"
#include "ghost.h"

/*
* represents an in-game ghost that is capable of climbing ladders.
*/
class BigGhost : public Ghost
{
    static constexpr double LADDER_CLIMB_PROB = 0.5;
    bool climbing = false;

public:
    /**
    * Constructor to initialize a big ghost as a ghost.
    * @param _pos: Initial position of the big ghost.
    * @param _dir: Initial direction of the big ghost.
    * @param _board: Pointer to the game board.
    */
    BigGhost(Point _pos, utils::Key _dir, Board* _board) : Ghost(_pos, _dir, _board) {}

    /**
     * Moves the ghost
     */
    void move(std::list<EntityPtr>& allEntities) override;

    /**
     * Draws the ghost on the board.
     */
    void draw(char ch = utils::ch_big_ghost) const override { Entity::draw(utils::ch_big_ghost); };

};

