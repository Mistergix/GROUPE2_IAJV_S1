#include "World.h"
#include <iostream>

void World::PlayerTakeDamage()
{
	playerLife--;
	if (playerLife <= 0) {
		playerLife = 0;
		std::cout << "Player Is Dead" << std::endl;
	}
}

int World::WeaponsLeftCount()
{
	return weaponsCount;
}

bool World::TakeWeapon()
{
	if (WeaponsLeftCount() >= 1) {
		weaponsCount--;
		return true;
	}

	return false;
}
