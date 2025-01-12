#include "ghost.h"
#include "board.h"
#include <cstdlib>



void Ghost::move(const std::list<Ghost>& allGhosts) {

    double random = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    if (random > SAME_DIR_PROB) {
        dir = (dir == LEFT) ? RIGHT : LEFT;
    }

    Point next_pos = pos.neighbor(dir);
    char next_tile = pBoard->getChar(next_pos);
    char below_tile = pBoard->getChar(next_pos.neighbor(DOWN));

    for (auto& ghost : allGhosts) {
        if (&ghost != this && ghost.getPos() == next_pos) {
            
            dir = (dir == LEFT) ? RIGHT : LEFT;
            return;
        }
    }

    if ( below_tile != ch_blank) {
        pos = next_pos;
    }
    else {
        //change direction 
        dir = (dir == LEFT) ? RIGHT : LEFT;
    }
}


void Ghost::draw(char ch) const { 
    pBoard->drawChar(ch, pos);
}

void Ghost::erase() const { 
    pBoard->restoreChar(pos); 
}