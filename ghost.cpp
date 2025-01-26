#include "entity.h"
#include "ghost.h"
#include "board.h"
#include <cstdlib>

using namespace utils;

void Ghost::move(std::list<EntityPtr>& allEntities)
{
    Key dir = Entity::getDir();
    Point pos = Entity::getPos();
    Board* pBoard = Entity::getBoard();
    Point next_pos;

    if (pBoard->getChar(pos.neighbor(Key::DOWN)) == ch_blank) { // fall down logic for poorly done .screen files
        next_pos = pos.neighbor(Key::DOWN);
        Entity::setPos(next_pos);
    }
    else {
        double random = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        if (random > SAME_DIR_PROB) {
            dir = (dir == Key::LEFT) ? Key::RIGHT : Key::LEFT;
            Entity::setDir(dir);
        }

        next_pos = pos.neighbor(dir);
        char next_tile = pBoard->getChar(next_pos);
        char below_tile = pBoard->getChar(next_pos.neighbor(Key::DOWN));

        for (auto& entity : allEntities) {
            if (auto ghost = dynamic_cast<Ghost*>(entity.get())) {
                if (ghost != this && entity->getPos() == next_pos) {
                    dir = (dir == Key::LEFT) ? Key::RIGHT : Key::LEFT;
                    Entity::setDir(dir);
                    return;
                }
            }
        }

        if (below_tile != ch_blank && (next_tile == ch_blank || next_tile == ch_ladder)) {
            Entity::setPos(next_pos);
        }
        else {
            //change direction 
            dir = (dir == Key::LEFT) ? Key::RIGHT : Key::LEFT;
            Entity::setDir(dir);
        }
    }
}