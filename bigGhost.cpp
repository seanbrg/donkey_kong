#include "entity.h"
#include "ghost.h"
#include "bigGhost.h"
#include "board.h"
#include <cstdlib>

using namespace utils;

void BigGhost::move(std::list<EntityPtr>& allEntities)
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
        double random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

        if (climbing) {
            next_pos = pos.neighbor(dir);
            char next_tile = pBoard->getChar(next_pos);
            char below_tile = pBoard->getChar(next_pos.neighbor(Key::DOWN));
            Entity::setPos(next_pos);
            
            // end the climb if reached top or bottom of a ladder:
            if ((dir == Key::UP && next_tile == ch_blank) ||
                (dir == Key::DOWN && below_tile != ch_ladder)) {
                climbing = false;
                dir = (random > DECIDE_DIR_PROB) ? Key::RIGHT : Key::LEFT;
                Entity::setDir(dir);
            }
        }
        else {
            if (random > LADDER_CLIMB_PROB) {
                if (pBoard->getChar(pos) == ch_ladder) {
                    climbing = true;
                    dir = Key::UP;
                    Entity::setDir(dir);
                }
                else if (pBoard->getChar(pos.neighbor(Key::DOWN)) == ch_ladder) {
                    climbing = true;
                    dir = Key::DOWN;
                    Entity::setDir(dir);
                }
            }
            else if (random > SAME_DIR_PROB) {
                dir = (dir == Key::LEFT) ? Key::RIGHT : Key::LEFT;
                Entity::setDir(dir);
            }

            next_pos = pos.neighbor(dir);
            char next_tile = pBoard->getChar(next_pos);
            char below_tile = pBoard->getChar(next_pos.neighbor(Key::DOWN));

            for (auto& entity : allEntities) {
                if (auto ghost = dynamic_cast<Ghost*>(entity.get())) {
                    if (ghost != dynamic_cast<Ghost*>(this) && entity->getPos() == next_pos) {
                        if (climbing)
                            dir = (dir == Key::UP) ? Key::DOWN : Key::UP;
                        else
                            dir = (dir == Key::LEFT) ? Key::RIGHT : Key::LEFT;

                        Entity::setDir(dir);
                        return;
                    }
                }
            }

            if (below_tile != ch_blank) {
                Entity::setPos(next_pos);
            }
            else {
                //change direction 
                dir = (dir == Key::LEFT) ? Key::RIGHT : Key::LEFT;
                Entity::setDir(dir);
            }
        }
    }
}