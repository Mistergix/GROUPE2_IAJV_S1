#include "Action_MoveToPlayer.h"
#include <iostream>

Action_MoveToPlayer::Action_MoveToPlayer():
	GoapAction(3, "MoveToPlayer")
{
	addEffect("is_in_range_distance", true);
	timeToMove = 2.5f;
	reset();
}

bool Action_MoveToPlayer::tryPerformAction(WorldV2& world, GoapAgent& ai)
{
	currentTimeToMove += 1.0f / 60.0f;
	std::cout << "Moving to player, completion " << currentTimeToMove / timeToMove * 100.0f << std::endl;
	return true;
}

bool Action_MoveToPlayer::finished() const
{
	return currentTimeToMove >= timeToMove;
}

bool Action_MoveToPlayer::canDoActionInContext(WorldV2& world, GoapAgent& ai) const
{
	return true;
}

void Action_MoveToPlayer::reset()
{
	currentTimeToMove = 0.0f;
}
