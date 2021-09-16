#include "Action_PickupWeapon.h"
#include <iostream>

Action_PickupWeapon::Action_PickupWeapon():
	GoapAction(3, "PickupWeapon")
{
	addEffect("is_in_range", false);
	addEffect("has_weapon", true);
	addEffect("has_ammo", true);

	timeToGetWeapon = 1.5f;
	reset();
}

bool Action_PickupWeapon::tryPerformAction(WorldV2& world, GoapAgent& ai)
{
	currentTimeToGetWeapon += 1.0f / 60.0f;
	std::cout << "Going To Weapon, completion " << currentTimeToGetWeapon / timeToGetWeapon * 100.0f << std::endl;

	if (finished()) {
		return (world.TakeWeapon());
	}
	return true;
}

bool Action_PickupWeapon::finished() const
{
	return currentTimeToGetWeapon >= timeToGetWeapon;
}

bool Action_PickupWeapon::canDoActionInContext(WorldV2& world, GoapAgent& ai) const
{
	return true;
}

void Action_PickupWeapon::reset()
{
	currentTimeToGetWeapon = 0.0f;
}

