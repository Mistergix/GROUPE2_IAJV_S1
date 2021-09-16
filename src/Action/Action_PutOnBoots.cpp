#include "Action_PutOnBoots.h"
#include <iostream>

Action_PutOnBoots::Action_PutOnBoots() :
	GoapAction(3, "PutOnBoots")
{
	addEffect("has_boots", true);

	reset();
}

bool Action_PutOnBoots::tryPerformAction(WorldV2& world, GoapAgent& ai)
{
	std::cout << "Put on boots " << std::endl;
	_finished = true;
	return true;
}

bool Action_PutOnBoots::finished() const
{
	return _finished;
}

bool Action_PutOnBoots::canDoActionInContext(WorldV2& world, GoapAgent& ai) const
{
	return true;
}

void Action_PutOnBoots::reset()
{
	_finished = false;
}