#include "Map.h"

Map::Map(int rows, int columns, int numOfEnemies)
	: m_mapRows {rows}, m_mapColumns {columns}, m_numOfRooms {rows * columns}, m_enemyRoom{1, m_numOfRooms - 1}
{

	for (int rowNum = 1; rowNum <= rows; ++rowNum)
	{
		for (int columnNum = 1; columnNum <= columns; ++columnNum)
		{
			rooms.push_back(Room{columnNum, rowNum});
		}
	}

	addEnemiesToRooms(numOfEnemies);
}


std::string Map::getMapString(Player& p) const
{
	std::string mapString {};
	for (Room room : rooms)
	{
		if (room.containsPlayer(p))
		{
			mapString.push_back('P');
		}
		else if (room.containsEnemy())
		{
			mapString.push_back('E');
		}
		else
		{
			mapString.push_back('#');
		}

		// New row
		if (room.getRoomX() == m_mapColumns)
		{
			mapString.push_back('\n');
		}
	}

	return mapString;
}


std::vector<Room>& Map::getMap()
{
	return rooms;
}


int Map::getRoomIndexFromCoords(int xCoord, int yCoord) const
{
	// Find the vector index of a room based off of its coordinates.

	// roomIndex is unsigned to quell the compiler's "signed/unsigned comparison" warning
	unsigned int roomIndex{0};
	for (; roomIndex < rooms.size(); ++roomIndex)
	{
		if (rooms.at(roomIndex).getRoomX() == xCoord && rooms.at(roomIndex).getRoomY() == yCoord)
		{
			break;
		}
	}

	return roomIndex;
}

int Map::getRoomIndexFromCoords(std::pair<int, int> coords) const
{
	unsigned int roomIndex{ 0 };
	for (; roomIndex < rooms.size(); ++roomIndex)
	{
		if (rooms.at(roomIndex).getRoomX() == coords.first && rooms.at(roomIndex).getRoomY() == coords.second)
		{
			break;
		}
	}

	return roomIndex;
}


std::pair<int, int> Map::getCoordsFromRoomIndex(int index) const
{
	std::pair<int, int> roomCoords {rooms.at(index).getRoomX(), rooms.at(index).getRoomY()};
	return roomCoords;
}


void Map::addEnemiesToRooms(int numOfEnemies)
{
	// Add enemies randomly distributed throughout the rooms, only 1 per room.
	// Enemy cannot occupy first room (A.K.A. rooms vector index 0)

	while (numOfEnemies > 0)
	{
		int indexToAddEnemyTo = m_enemyRoom(s_mersenneTwister);

		// Brute-force logic to add only 1 enemy to each room.
		if (rooms.at(indexToAddEnemyTo).containsEnemy())
		{
			continue;
		}
		else
		{
			std::pair<int, int> coords = getCoordsFromRoomIndex(indexToAddEnemyTo);
			Enemy enemyToAdd{coords.first, coords.second};
			rooms.at(indexToAddEnemyTo).addRoomEnemy(enemyToAdd);
			--numOfEnemies;
		}
	}
}


std::random_device Map::s_randomDevice{};
std::mt19937 Map::s_mersenneTwister{ Map::s_randomDevice() };