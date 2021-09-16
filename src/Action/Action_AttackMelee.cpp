#include "Action_AttackMelee.h"
#include <iostream>

Action_AttackMelee::Action_AttackMelee() :
	GoapAction(1, "AttackPlayerMelee")
{
	addPrecondition("is_in_range_melee", true);

	reset();
}

bool Action_AttackMelee::tryPerformAction(WorldV2& world, GoapAgent& ai)
{
	std::cout << "ATTACK PLAYER MELEE, his life is " << world.playerLife << std::endl;
	world.PlayerTakeDamage();
	std::cout << "His life now is " << world.playerLife << std::endl;
	_finished = true;
	return true;
}

bool Action_AttackMelee::finished() const
{
	return _finished;
}

bool Action_AttackMelee::canDoActionInContext(WorldV2& world, GoapAgent& ai) const
{
	return true;
}

void Action_AttackMelee::reset()
{
	_finished = false;
}