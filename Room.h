#ifndef ROOM_H
#define ROOM_H


#include "Enemy.h"

#include <utility>
#include <vector>

#include "Player.h"

class Room
{
public:
	Room(int xCoord=-1, int yCoord=-1);
	int getRoomX() const;
	int getRoomY() const;
	const std::pair<int, int>& getRoomCoords() const;
	bool containsEnemy() const;
	bool containsPlayer(Player& player) const;
	void addRoomEnemy(Enemy addedEnemy);
	void removeRoomEnemy();
	std::vector<Enemy>& getEnemies();
private:
	std::pair<int, int> m_roomCoords{};
	std::vector<Enemy> m_enemiesInRoom{};
};

#endif