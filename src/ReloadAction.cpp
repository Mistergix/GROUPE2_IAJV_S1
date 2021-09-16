#include "ReloadAction.h"

ReloadAction::ReloadAction(float cost, float reloadTime) : GoapAction(cost), reloadTime(reloadTime)
{
	AddPreCondition("HasWeapon", true);

	AddEffect("HasAmmo", true);

	Reset();
}

bool ReloadAction::TryPerformAction(World world)
{
	currentReloadTime += 1.0f / 60.0f;
	return true;
}

bool ReloadAction::Finished()
{
	return currentReloadTime >= reloadTime;
}

bool ReloadAction::CanDoActionInContext(GoapAI& ai, World& world) const
{
	return true;
}

void ReloadAction::Reset()
{
	currentReloadTime = 0.0f;
}
