#include "Enemy.h"

Enemy::Enemy(int x, int y, int health, int attack, int defense)
	: Entity{health, attack, defense}
{
	setPosition(x, y);
}