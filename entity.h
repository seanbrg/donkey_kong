#pragma once
#include "utils.h"
#include "point.h"
#include <list>

class Board;

class Entity
{
    Point pos;
    Key dir;
    Board* pBoard;

protected:

    void setPos(Point& new_pos) { pos = new_pos; }

    void setDir(Key new_dir) { dir = new_dir; }
    
    Key getDir() const { return dir; }
    
    Board* getBoard() const { return pBoard; }

public:
    Entity(Point _pos, Key _dir, Board* _board) : pos(_pos), dir(_dir), pBoard(_board) {}

    /**
     * Moves the entity
     */
    virtual void move(std::list<Entity*>& allEntities) = 0;

    /**
     * Draws the entity on the board.
     */
    virtual void draw(char ch = ' ') const;

    /**
     * Erases the entity from the board.
     */
    void erase() const;

    /**
     * Gets the current position of the entity.
     */
    Point getPos() const { return pos; }

    /**
     * Sets the direction of the entity.
     */
    void setDirection(Key newDir) { dir = newDir; }

};

