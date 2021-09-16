#pragma once

#include <list>
#include <deque>
#include <unordered_map>
#include <string>
#include "Action/GoapAction.h"

struct GoapNode
{
	std::unordered_map<std::string, bool> remainingPreconditions;
	std::list<GoapAction*> remainingActions;
	GoapAction* currentAction = nullptr;
	
	GoapNode* parent = nullptr;
	std::list<GoapNode> children;
};
