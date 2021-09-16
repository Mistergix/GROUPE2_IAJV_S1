#include "WorldV2.h"
#include <iostream>

void WorldV2::PlayerTakeDamage()
{
	playerLife--;
	if (playerLife <= 0) {
		playerLife = 0;
		std::cout << "Player Is Dead" << std::endl;
	}
}

int WorldV2::WeaponsLeftCount()
{
	return weaponsCount;
}

bool WorldV2::TakeWeapon()
{
	if (WeaponsLeftCount() >= 1) {
		std::cout << "Picked up a weapon, only " << (weaponsCount - 1) << " left in the world" << std::endl;
		weaponsCount--;
		return true;
	}

	std::cout << "No weapon left ..." << std::endl;

	return false;
}