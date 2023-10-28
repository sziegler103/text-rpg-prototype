#ifndef ENTITY_H
#define ENTITY_H

#include <utility>

class Entity
{
public:
	Entity(int health=0, int attack=0, int defense=0);
	int getHealth() const;
	void setHealth(int health);
	int getMaxHealth() const;
	int getAttack() const;
	void setAttack(int attack);
	void receiveDamage(int attackDmg);
	int getDefense() const;
	void setDefense(int defense);
	bool isDefending();
	void setDefending(bool defending);
	int getCurrentDefense() const;
	std::pair<int, int> getPosition() const;
	int getPositionX() const;
	int getPositionY() const;
	void setPosition(int xPos, int yPos);
	enum directions
	{
		NORTH = 1,
		EAST,
		SOUTH,
		WEST,
	};
private:
	int m_health {};
	int m_maxHealth {};
	int m_attack {};
	int m_defense {};
	int m_curDefense {};
	bool m_defending {};
	std::pair<int, int> m_position {};
};

#endif