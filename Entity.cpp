#include "Entity.h"

Entity::Entity(int health, int attack, int defense)
	: m_health {health}, 
	m_maxHealth {health}, 
	m_attack {attack}, 
	m_defense {defense},
	m_curDefense {defense}
{

}

int Entity::getHealth() const
{
	return m_health;
}

void Entity::setHealth(int health)
{
	m_health = health;
}

int Entity::getMaxHealth() const
{
	return m_maxHealth;
}

int Entity::getAttack() const
{
	return m_attack;
}

void Entity::setAttack(int attack)
{
	m_attack = attack;
}

void Entity::receiveDamage(int attackDmg)
{
	int currentDefense = m_curDefense;
	if (currentDefense > attackDmg)
	{
		currentDefense = attackDmg;
	}
	m_health -= (attackDmg - currentDefense);
}

int Entity::getDefense() const
{
	return m_defense;
}

void Entity::setDefense(int defense)
{
	m_defense = defense;
}

bool Entity::isDefending()
{
	return m_defending;
}

void Entity::setDefending(bool defending)
{
	if (defending)
	{
		m_curDefense = m_defense + 2;
	}
	else
	{
		m_curDefense = m_defense;
	}
	m_defending = defending;
}

int Entity::getCurrentDefense() const
{
	return m_curDefense;
}

std::pair<int, int> Entity::getPosition() const
{
	return m_position;
}

int Entity::getPositionX() const
{
	return m_position.first;
}

int Entity::getPositionY() const
{
	return m_position.second;
}

void Entity::setPosition(int xPos, int yPos)
{
	m_position.first = xPos;
	m_position.second = yPos;
}