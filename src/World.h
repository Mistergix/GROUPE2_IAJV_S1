#pragma once 

class World {
public :
	int playerLife;
	World(int playerLife) : playerLife(playerLife) {
		weaponsCount = 1;
	}
	void PlayerTakeDamage();
	int WeaponsLeftCount();
	bool TakeWeapon();

private:
	int weaponsCount;
};