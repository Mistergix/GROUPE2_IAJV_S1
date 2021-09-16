#pragma once 

class WorldV2 {
public:
	int playerLife;
	WorldV2(int playerLife, int weaponsCount) : playerLife(playerLife), weaponsCount(weaponsCount) {
		
	}
	void PlayerTakeDamage();
	int WeaponsLeftCount();
	bool TakeWeapon();
	void update();

private:
	int weaponsCount;
};