#include "IdleAction.h"
#include <iostream>

IdleAction::IdleAction(float cost, std::string name) : GoapAction(cost, name)
{
}

bool IdleAction::TryPerformAction(World& world, GoapAI& ai)
{
	std::cout << "I AM IDLING" << std::endl;
	return true;
}

bool IdleAction::Finished() const
{
	//Finish directly to try recompute a new plan
	return true;
}

bool IdleAction::CanDoActionInContext(World& world, GoapAI& ai) const
{
	return true;
}

void IdleAction::Reset()
{
}
