#include "ReloadAction.h"

void ReloadAction::GeneratePreConditions()
{
	AddPreCondition("HasWeapon", true);
}

void ReloadAction::GenerateEffects()
{
	AddEffect("HasAmmo", true);
}

bool ReloadAction::TryPerformAction(World world)
{
	currentReloadTime += 1.0f / 60.0f;
	return true;
}

bool ReloadAction::Finished()
{
	return false;
}

bool ReloadAction::CanDoAction(GoapAI& ai) const
{
	return false;
}

void ReloadAction::Reset()
{
	currentReloadTime = 0.0f;
}
