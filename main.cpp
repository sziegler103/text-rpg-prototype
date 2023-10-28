/* Text-based RPG foundation
 * by Stephen Ziegler, for CS 1410 with Instructor Kim Murphy
 *
 * Program implements what could be, in a perfect world, 
 * a more fleshed-out and less spaghetti-code-esque text-based RPG.
 */

#include "Room.h"
#include "Map.h"
#include "Player.h"

#include <iostream>
#include <utility>
#include <random>


bool playerIsInBounds(Player& p, Map& m);
bool playerInHostileRoom(Player& p, Map& m);
void combat(Player& p, Enemy& e);


int main()
{
	// Adjustable constants
	constexpr int mapSizeX		{ 5 };
	constexpr int mapSizeY		{ 6 };
	constexpr int numOfEnemies	{ 5 };

	constexpr int playerHealth	{ 20 };
	constexpr int playerAttack	{ 8 };
	constexpr int playerDefense	{ 3 };


	// Initialize
	Map map{mapSizeY, mapSizeX, numOfEnemies};
	Player player{playerHealth, playerAttack, playerDefense};
	bool enemiesRemaining {true};


	// Primary game loop
	while (enemiesRemaining)
	{
		system("cls");

		std::cout << map.getMapString(player) << '\n';
		std::cout << "Where do you want to move?\n";
		std::cout << "1 for North; 2 for East; 3 for South, 4 for West; 5 for quit\n";

		int userChoice {};
		std::cin >> userChoice;
		
		if (userChoice == 5) // If user wants to quit, do so.
		{
			break;
		}
		else // Otherwise, move the player and check their position.
		{
			std::pair<int, int> lastPos {player.getPosition()};
			player.move(userChoice);
			if (!playerIsInBounds(player, map)) // If player goes out of bounds, reset them to their last position.
			{
				player.setPosition(lastPos.first, lastPos.second);
			}
		}

		if (playerInHostileRoom(player, map)) // If player moves into a room with an enemy, initate combat
		{
			system("cls");

			std::pair<int, int> playerPosition{ player.getPosition() };
			std::vector<Room>& rooms = map.getMap();
			Room& currentRoom = rooms.at(map.getRoomIndexFromCoords(playerPosition));
			Enemy& roomEnemy = currentRoom.getEnemies().at(0);
			
			combat(player, roomEnemy);

			if (player.getHealth() < 1) // If the player is dead, end the game.
			{
				system("cls");
				player.setPosition(0, 0);
				std::cout << map.getMapString(player) << "\n\n";

				std::cout << "You have been slain by an enemy.\n";
				std::cout << "\n---------\n";
				std::cout << "GAME OVER\n";
				std::cout << "---------\n\n";
				system("pause");
				break;
			}

			currentRoom.removeRoomEnemy(); // If player survived, clean up the enemy.
		}

		// Check for any enemies remaining on the map. If there are, the player hasn't won. Set enemiesRemaining to reflect as such.
		for (Room room : map.getMap())
		{
			if (room.containsEnemy())
			{
				enemiesRemaining = true;
				break;
			}
			else
			{
				enemiesRemaining = false;
			}
		}
	}

	// If there are no enemies remaining, the player has won. Say so and end the game.
	if (!enemiesRemaining)
	{
		system("cls");
		std::cout << map.getMapString(player) << "\n\n";

		std::cout << "You cleared all of the enemies.\n";
		std::cout << "\n--------\n";
		std::cout << "YOU WIN!\n";
		std::cout << "--------\n\n";

		std::cout << '\n';
		system("pause");
	}

	return 0;
}


bool playerIsInBounds(Player& p, Map& m)
{
	bool inBounds{};
	int playerX = p.getPositionX();
	int playerY = p.getPositionY();

	if (playerX < 1 || playerY < 1) // Check for left or up out of bounds
	{
		inBounds = false;
	}
	else if (playerX > m.m_mapColumns || playerY > m.m_mapRows)
	{
		inBounds = false;
	}
	else
	{
		inBounds = true;
	}

	return inBounds;
}

bool playerInHostileRoom(Player& p, Map& m) // If the room matching the player's coordinates has an enemy, they're in a hostile room.
{
	bool inEnemyRoom{false};

	std::pair<int, int> playerPosition{ p.getPosition() };
	const std::vector<Room>& rooms = m.getMap();
	const Room& currentRoom = rooms.at(m.getRoomIndexFromCoords(playerPosition));

	if (currentRoom.containsEnemy())
	{
		inEnemyRoom = true;
	}

	return inEnemyRoom;
}

void combat(Player& p, Enemy& e)
{
	// Print initial information.
	std::cout << "You encountered an enemy!";
	std::cout << "\n\nEnemy Stats:\n";
	std::cout << "Health: " << e.getHealth() << '/' << e.getMaxHealth() << '\n';
	std::cout << "Attack: " << e.getAttack() << '\n';
	std::cout << "Defense: " << e.getDefense();

	std::cout << "\n\nYour Stats:\n";
	std::cout << "Health: " << p.getHealth() << '/' << p.getMaxHealth() << '\n';
	std::cout << "Attack: " << p.getAttack() << '\n';
	std::cout << "Defense: " << p.getDefense();

	// Initialize random number generator and uniform distributions based off of the player and enemy's attack stat
	std::mt19937 RNG {std::random_device{}()};
	std::uniform_int_distribution<> enemyDefendDecision {1, 10};
	std::uniform_int_distribution<> playerDamage {1, p.getAttack()};
	std::uniform_int_distribution<> enemyDamage {1, e.getAttack()};

	int turnNumber {1};

	while (e.getHealth() > 0)
	{
		std::cout << "\n\n\n\\/\\/\\/\\/\\/\\/ TURN NUMBER " << turnNumber << " \\/\\/\\/\\/\\/\\/";


		// ====================Player's turn====================
		std::cout << "\nYour health: " << p.getHealth() << '/' << p.getMaxHealth() << '\n';
		std::cout << "\nEnemy's Health: " << e.getHealth() << '/' << e.getMaxHealth() << '\n';

		std::cout << "\nWhat would you like to do?";
		std::cout << "\n1 for Attack; 2 for Defend: ";

		int userChoice{};
		std::cin >> userChoice;

		if (userChoice == 1) // Player chooses to attack
		{
			int dealtDamage = playerDamage(RNG);
			e.receiveDamage(dealtDamage);
			if (dealtDamage <= e.getCurrentDefense())
			{
				// Damage was less than or equal to opponents defense.
				std::cout << "\n===>You don't deal any damage!<===\n";
			}
			else
			{
				std::cout << "\n===>You deal " << (dealtDamage - e.getCurrentDefense()) << " damage<===\n";
			}
		}
		else if (userChoice == 2) // Player chooses to defend
		{
			p.setDefending(true); // If defending, defense stat has +2 added to it.
			std::cout << "\nYou prepare to defend against a strike.\n";
		}
		e.setDefending(false); // If enemy was defending the previous turn, revert it.


		// ====================Enemy's turn====================
		std::cout << "\n----------------------------------------";
		if (enemyDefendDecision(RNG) >= 2) // 20% chance for enemy to choose to defend, otherwise, attack.
		{
			int dealtDamage = enemyDamage(RNG);
			std::cout << "\nThe enemy attacks!\n";
			p.receiveDamage(dealtDamage);
			if (dealtDamage <= p.getCurrentDefense())
			{
				// Damage was less than or equal to opponents defense.
				std::cout << "===>The enemy's blow glances off your armor!<===\n";
			}
			else
			{
				std::cout << "===>You receive " << (dealtDamage - p.getCurrentDefense()) << " damage<===\n";
			}
		}
		else
		{
			std::cout << "\nThe enemy puts up a defensive stance.\n";
			e.setDefending(true);
		}
		p.setDefending(false); // Revert player's defensive state if they defended on their turn.
		std::cout << "----------------------------------------";

		if (p.getHealth() < 1) // If player is dead, break out of the combat loop.
		{
			break;
		}

		++turnNumber;
	}

	if (e.getHealth() < 1) // If the enemy died instead, print as such.
	{
		std::cout << "\n\n\nYou have slain the enemy.\n\n";
		system("pause");
	}
}