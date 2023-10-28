#include "Player.h"

Player::Player(int health, int attack, int defense)
	: Entity{health, attack, defense}
{
	setPosition(1, 1);
}

void Player::move(int direction)
{
	switch (direction)
	{
	case NORTH:
		setPosition(getPositionX(), getPositionY() - 1);
		break;
	case EAST:
		setPosition(getPositionX() + 1, getPositionY());
		break;
	case SOUTH:
		setPosition(getPositionX(), getPositionY() + 1);
		break;
	case WEST:
		setPosition(getPositionX() - 1, getPositionY());
		break;
	}
}
