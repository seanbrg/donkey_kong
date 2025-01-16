#include "entity.h"
#include "ghost.h"
#include "board.h"
#include <cstdlib>

void Ghost::move(std::list<EntityPtr>& allEntities)
{
    Key dir = Entity::getDir();
    Point pos = Entity::getPos();
    Board* pBoard = Entity::getBoard();

    double random = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    if (random > SAME_DIR_PROB) {
        dir = (dir == LEFT) ? RIGHT : LEFT;
        Entity::setDir(dir);
    }

    Point next_pos = pos.neighbor(dir);
    char next_tile = pBoard->getChar(next_pos);
    char below_tile = pBoard->getChar(next_pos.neighbor(DOWN));

    for (auto& entity : allEntities) {
        if (typeid(*entity) == typeid(Ghost)) {
            if (entity.get() != this && entity->getPos() == next_pos) {
                dir = (dir == LEFT) ? RIGHT : LEFT;
                Entity::setDir(dir);
                return;
            }
        }
    }

    if ( below_tile != ch_blank) {
        Entity::setPos(next_pos);
    }
    else {
        //change direction 
        dir = (dir == LEFT) ? RIGHT : LEFT;
        Entity::setDir(dir);
    }
}