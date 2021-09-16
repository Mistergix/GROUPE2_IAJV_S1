#include "Action_Reload.h"
#include<iostream>

Action_Reload::Action_Reload():
	GoapAction(1, "Reload")
{
	addPrecondition("has_weapon", true);
	addEffect("has_ammo", true);

	reloadTime = 1.0f;
	reset();
}

bool Action_Reload::tryPerformAction(WorldV2& world, GoapAgent& ai)
{
	currentReloadTime += 1.0f / 60.0f;
	std::cout << "Going To Weapon, completion " << currentReloadTime / reloadTime * 100.0f << std::endl;
	return true;
}

bool Action_Reload::finished() const
{
	return currentReloadTime >= reloadTime;
}

bool Action_Reload::canDoActionInContext(WorldV2& world, GoapAgent& ai) const
{
	return true;
}

void Action_Reload::reset()
{
	currentReloadTime = 0.0f;
}
