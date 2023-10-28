#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

#include <iostream>
#include <utility>

class Player : public Entity
{
public:
	Player(int health=30, int attack=5, int defense=2);
	void move(int direction);
};

#endif