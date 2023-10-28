#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

class Enemy : public Entity
{
public:
	Enemy(int x, int y, int health=10, int attack=6, int defense=2);
private:

};

#endif