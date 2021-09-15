#include "ReloadAction.h"

ReloadAction::ReloadAction(float cost) : GoapAction(cost)
{
	
}

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
	return currentReloadTime >= reloadTime;
}

bool ReloadAction::CanDoAction(GoapAI& ai) const
{
	return true;
}

void ReloadAction::Reset()
{
	currentReloadTime = 0.0f;
}
