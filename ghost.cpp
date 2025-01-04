#include "Ghost.h"
#include "Board.h"  

Ghost::Ghost(Point _pos, Key _dir, Board* _b)
    : pos(_pos), dir(_dir), board(_b) {}

void Ghost::move() {
    
    /*if (rand() % 100 < 5) {  // 5% chance to change direction
        dir = LEFT;
    }*/

    /*Point new_pos = pos.neighbor(dir);//pos based on current direction
    char tileAtNewPos = board->getChar(newPos);

    
    if (tileAtNewPos == ' ') {
        pos = new_pos;
    }
    else {
        reverseDirection();
    }*/
	
	
    Point new_pos = pos.neighbor(dir);

	pos = new_pos;

	

}


bool Ghost::detectMario(Point marioPos) {
    return pos == marioPos; 
}

void Ghost::reverseDirection() {
    
    if (dir == LEFT) {
        dir = RIGHT;
    }
    else if (dir == RIGHT) {
        dir = LEFT;
    }
}


void Ghost::draw() const {
    board->drawChar('X', pos);
}
