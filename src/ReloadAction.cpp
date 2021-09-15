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
	return false;
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
}
