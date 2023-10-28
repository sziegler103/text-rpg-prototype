#ifndef MAP_H
#define MAP_H

#include "Player.h"
#include "Room.h"

#include <string>
#include <utility>
#include <random>

class Map
{
private:
	int m_numOfRooms{};

public:
	Map(int rows=6, int columns=5, int numOfEnemies=6);
	int getRoomIndexFromCoords(int xCoord, int yCoord) const;
	int getRoomIndexFromCoords(std::pair<int, int> coords) const;
	std::pair<int, int> getCoordsFromRoomIndex(int index) const;
	std::string getMapString(Player& p) const;
	std::vector<Room>& getMap();

	int m_mapRows{};
	int m_mapColumns{};
	double enemyChance{ 1.0 / static_cast<double>(m_numOfRooms) };

private:
	std::vector<Room> rooms {};
	void addEnemiesToRooms(int numOfEnemies);
	std::uniform_int_distribution<> m_enemyRoom;
	static std::random_device s_randomDevice;
	static std::mt19937 s_mersenneTwister;
};

#endif