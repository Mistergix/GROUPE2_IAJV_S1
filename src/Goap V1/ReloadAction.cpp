#include "ReloadAction.h"
#include <iostream>

ReloadAction::ReloadAction(float cost, std::string name) : GoapActionV1(cost, name)
{
	AddPreCondition("HasWeapon", true);

	AddEffect("HasAmmo", true);

	Reset();
}

bool ReloadAction::TryPerformAction(World& world, GoapAI& ai)
{
	currentReloadTime += 1.0f / 60.0f;
	std::cout << "Going To Weapon, completion " << currentReloadTime / reloadTime * 100.0f << std::endl;
	return true;
}

bool ReloadAction::Finished() const
{
	return currentReloadTime >= reloadTime;
}

bool ReloadAction::CanDoActionInContext(World& world, GoapAI& ai) const
{
	return true;
}

void ReloadAction::Reset()
{
	currentReloadTime = 0.0f;
}
