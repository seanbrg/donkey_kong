#pragma once
#include <Windows.h>
#include "utils.h"
#include "point.h"
#include "entity.h"

using namespace keys;

class Board;

/**
 * class representing a barrel in the game.
 * the barrel can move, fall, explode, and interact with the board.
 */
class Barrel : public Entity {
	bool active = true;
	bool explode = false;
	int fall_counter = 0;

public:

	/**
	 * constructor to initialize a barrel with a position, direction, and board reference.
	 * @param _pos: initial position of the barrel.
	 * @param _dir: initial direction of the barrel.
	 * @param _board: pointer to the game board.
	 */
	Barrel (const Point& _pos, Key _dir, Board* _board) : Entity(_pos, _dir, _board) {}

	/**
	 * moves the barrel based on its current state and the board.
	 */
	void move(std::list<Entity*>& allEntities) override;

	/**
	 * draws the barrel on the board.
	 */
	void draw(char ch = ch_barrel) const override { Entity::draw(ch); };


	/**
	 * draws the explosion effect for the barrel.
	 */
	void drawExplosion() const;
	
	/**
	 * checks if the barrel is exploding.
	 * @return true if the barrel is exploding, false otherwise.
	 */
	bool isExploding() const { return explode; }

	/**
	 * checks if the barrel is active.
	 * @return true if the barrel is active, false otherwise.
	 */
	bool exists() const { return active; }
};

