#include "Action_MoveToPlayerMelee.h"
#include <iostream>

Action_MoveToPlayerMelee::Action_MoveToPlayerMelee() :
	GoapAction(5, "MoveToPlayerMelee")
{
	addPrecondition("has_boots", true);
	addEffect("is_in_range_melee", true);
	timeToMove = 2.5f;
	reset();
}

bool Action_MoveToPlayerMelee::tryPerformAction(WorldV2& world, GoapAgent& ai)
{
	currentTimeToMove += 1.0f / 60.0f;
	std::cout << "Moving to player, completion " << currentTimeToMove / timeToMove * 100.0f << std::endl;
	return true;
}

bool Action_MoveToPlayerMelee::finished() const
{
	return currentTimeToMove >= timeToMove;
}

bool Action_MoveToPlayerMelee::canDoActionInContext(WorldV2& world, GoapAgent& ai) const
{
	return true;
}

void Action_MoveToPlayerMelee::reset()
{
	currentTimeToMove = 0.0f;
}
