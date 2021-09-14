#include "GoapGoal.h"

GoapGoal::GoapGoal(std::string& name)
{
	this->name = name;
}

void GoapGoal::SetChildren(std::vector<GoapAction>& children)
{
	this->children = children;
}

float GoapGoal::Cost(std::vector<GoapAction>& actions)
{
	cheapestCost = std::numeric_limits<float>::max();
	float cost = 0.0f;
	std::vector<GoapAction> goapActions;
	for (const auto& child : children) {
		cost = child.Cost(goapActions);
	}
}
