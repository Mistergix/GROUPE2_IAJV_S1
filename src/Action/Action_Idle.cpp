#include "Action_Idle.h"
#include <iostream>

Action_Idle::Action_Idle() :
	GoapAction(0, "Idle")
{
}

bool Action_Idle::tryPerformAction(WorldV2& world, GoapAgent& ai)
{
	std::cout << "I AM IDLING" << std::endl;
	return true;
}

bool Action_Idle::finished() const
{
	return true;
}

bool Action_Idle::canDoActionInContext(WorldV2& world, GoapAgent& ai) const
{
	return true;
}

void Action_Idle::reset()
{
}
