#include "Room.h"

Room::Room(int xCoord, int yCoord)
	: m_roomCoords{xCoord, yCoord}
{

}

int Room::getRoomX() const
{
	return m_roomCoords.first;
}

int Room::getRoomY() const
{
	return m_roomCoords.second;
}

const std::pair<int, int>& Room::getRoomCoords() const
{
	return m_roomCoords;
}

bool Room::containsEnemy() const
{
	bool roomHasEnemy{};
	if (m_enemiesInRoom.empty())
	{
		roomHasEnemy = false;
	}
	else
	{
		roomHasEnemy = true;
	}

	return roomHasEnemy;
}

bool Room::containsPlayer(Player& player) const
{
	bool roomHasPlayer{};

	if (player.getPositionX() == m_roomCoords.first)
	{
		if (player.getPositionY() == m_roomCoords.second)
		{
			roomHasPlayer = true;
		}
	}

	return roomHasPlayer;
}

void Room::addRoomEnemy(Enemy addedEnemy)
{
	m_enemiesInRoom.push_back(addedEnemy);
}

void Room::removeRoomEnemy()
{
	m_enemiesInRoom.pop_back();
}

std::vector<Enemy>& Room::getEnemies()
{
	return m_enemiesInRoom;
}