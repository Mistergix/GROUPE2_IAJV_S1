#include "Action_Teleport.h"
#include<iostream>

Action_Teleport::Action_Teleport() :
	GoapAction(1, "Teleport")
{
	addPrecondition("has_teleporter", true);
	addEffect("has_teleporter", false);
	addEffect("is_in_range_distance", true);
	addEffect("is_in_range_melee", true);
	reset();
}

bool Action_Teleport::tryPerformAction(WorldV2& world, GoapAgent& ai)
{
	std::cout << "Teleport to player" << std::endl;
	_finished = true;
	return true;
}

bool Action_Teleport::finished() const
{
	return _finished;
}

bool Action_Teleport::canDoActionInContext(WorldV2& world, GoapAgent& ai) const
{
	return true;
}

void Action_Teleport::reset()
{
	_finished = false;
}
