#include "MoveToPlayerAction.h"
#include <iostream>

MoveToPlayerAction::MoveToPlayerAction(float cost, std::string name) : GoapAction(cost, name)
{
	AddEffect("PlayerInRange", true);
	timeToMove = 2.5f;
	Reset();
}

bool MoveToPlayerAction::TryPerformAction(World& world, GoapAI& ai)
{
	currentTimeToMove += 1.0f / 60.0f;
	std::cout << "Moving to player, completion " << currentTimeToMove / timeToMove * 100.0f << std::endl;
	return true;
}

bool MoveToPlayerAction::Finished() const
{
	return currentTimeToMove >= timeToMove;
}

bool MoveToPlayerAction::CanDoActionInContext(World& world, GoapAI& ai) const
{
	return true;
}

void MoveToPlayerAction::Reset()
{
	currentTimeToMove = 0.0f;
}
