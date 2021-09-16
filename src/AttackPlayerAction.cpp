#include "AttackPlayerAction.h"
#include <iostream>

AttackPlayerAction::AttackPlayerAction(float cost, std::string name) : GoapAction(cost, name)
{
	AddPreCondition("HasAmmo", true);
	AddPreCondition("HasWeapon", true);
	AddPreCondition("PlayerInRange", true);

	AddEffect("DecreasePlayerLife", true);
}

bool AttackPlayerAction::TryPerformAction(World& world, GoapAI& ai)
{
	std::cout << "ATTACK PLAYER, his life is " + world.playerLife << std::endl;
	world.PlayerTakeDamage();
	std::cout << "His life now is " + world.playerLife << std::endl;
	return false;
}

bool AttackPlayerAction::Finished() const
{
	return true;
}

bool AttackPlayerAction::CanDoActionInContext(World& world, GoapAI& ai) const
{
	return true;
}

void AttackPlayerAction::Reset()
{
}
