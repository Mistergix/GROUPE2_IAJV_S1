#include "Action_AttackPlayer.h"
#include <iostream>

Action_AttackPlayer::Action_AttackPlayer():
	GoapAction(1, "AttackPlayer")
{
	addPrecondition("has_weapon", true);
	addPrecondition("has_ammo", true);
	addPrecondition("is_in_range", true);

	reset();
}

bool Action_AttackPlayer::tryPerformAction(WorldV2& world, GoapAgent& ai)
{
	std::cout << "ATTACK PLAYER, his life is " << world.playerLife << std::endl;
	world.PlayerTakeDamage();
	std::cout << "His life now is " << world.playerLife << std::endl;
	_finished = true;
	return true;
}

bool Action_AttackPlayer::finished() const
{
	return _finished;
}

bool Action_AttackPlayer::canDoActionInContext(WorldV2& world, GoapAgent& ai) const
{
	return true;
}

void Action_AttackPlayer::reset()
{
	_finished = false;
}
