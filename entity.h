#pragma once
#include "utils.h"
#include "point.h"
#include <list>

class Board;
class Entity;
using EntityPtr = std::shared_ptr<Entity>; // smart pointer that has a destructor

/**
 * class representing a generic entity in the game.
 */
class Entity
{
    Point pos;
    Key dir;
    Board* pBoard;

protected:

    /**
     * sets the position of the entity to a new position.
     */
    void setPos(Point& new_pos) { pos = new_pos; }
    /**
     * sets the direction of the entity to a new direction.
     */
    void setDir(Key new_dir) { dir = new_dir; }

    /**
     * gets the current direction of the entity.
     */
    Key getDir() const { return dir; }
    /**
     * gets the pointer to the game board associated with the entity.
     */
    Board* getBoard() const { return pBoard; }

public:
    /**
     * constructs an Entity object.
     */
    Entity(Point _pos, Key _dir, Board* _board) : pos(_pos), dir(_dir), pBoard(_board) {}

    /**
     * Moves the entity
     */
    virtual void move(std::list<EntityPtr>& allEntities) = 0;

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