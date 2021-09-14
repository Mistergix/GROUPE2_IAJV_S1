#include "GoapGoal.h"

GoapGoal::GoapGoal(std::string& name)
{
	this->name = name;
}

void GoapGoal::SetChildren(std::vector<GoapAction>& children)
{
	this->children = children;
}
