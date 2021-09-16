#include "GetWeaponAction.h"
#include <iostream>

GetWeaponAction::GetWeaponAction(float cost, std::string name) : GoapActionV1(cost, name)
{
	AddEffect("HasAmmo", true);
	AddEffect("HasWeapon", true);
	AddEffect("PlayerInRange", false);

	timeToGetWeapon = 1.5f;
	Reset();
}

bool GetWeaponAction::TryPerformAction(World& world, GoapAI& ai)
{
	currentTimeToGetWeapon += 1.0f / 60.0f;
	std::cout << "Going To Weapon, completion " << currentTimeToGetWeapon / timeToGetWeapon * 100.0f << std::endl;

	if (Finished()) {
		return (world.TakeWeapon());
	}

	return true;
}

bool GetWeaponAction::Finished() const
{
	return currentTimeToGetWeapon >= timeToGetWeapon;
}

bool GetWeaponAction::CanDoActionInContext(World& world, GoapAI& ai) const
{
	return world.WeaponsLeftCount() >= 1;
}

void GetWeaponAction::Reset()
{
	currentTimeToGetWeapon = 0.0f;
}
