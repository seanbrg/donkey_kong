#include "Ghost.h"
#include "Board.h"  

Ghost::Ghost(Point _pos, Key _dir, Board* _b)
    : pos(_pos), dir(_dir), board(_b) {}

void Ghost::move() {
    Point newPos = pos.neighbor(dir);
   

    char tileAtNewPos = board->getChar(newPos);

    pos = newPos;

    
   /**if (tileAtNewPos == '=' || tileAtNewPos == '<' || tileAtNewPos == '>') {
        
        pos = newPos;
    }
    else {
        // If it's not a floor, reverse direction and check again
        reverseDirection(); // Ensure this properly updates the direction
        newPos = position.neighbor(direction);

        // Check again if the new position is valid
        tileAtNewPos = board->getChar(newPos);
        if (tileAtNewPos == '=' || tileAtNewPos == '<' || tileAtNewPos == '>') {
            position = newPos;  // Update the position after reversing direction
        }
    }

    // Optional: Check if ghost encounters another ghost
    /*for (auto& ghost : board->getGhosts()) {
        if (ghost.position == position) {
            changeDirection();
            ghost.changeDirection();
        }
    }*/
}

bool Ghost::detectMario(Point marioPos) {
    return pos == marioPos; 
}

void Ghost::reverseDirection() {
    
    if (dir == UP) dir = DOWN;
    else if (dir == DOWN) dir = UP;
    else if (dir == LEFT) dir = RIGHT;
    else if (dir == RIGHT) dir = LEFT;
   
}

void Ghost::draw() const {
    board->drawChar('X', pos);
}
