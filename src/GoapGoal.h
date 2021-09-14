#pragma once
#include <string>
#include <vector>
#include "GoapAction.h"

class GoapGoal {
public:
	GoapGoal(std::string& name);
	void SetChildren(std::vector<GoapAction>& children);
	float Cost(std::vector<GoapAction>& actions);
private :
	std::string name;
	std::vector<GoapAction> children;
	float cheapestCost;
};