#pragma once

#include "Action/GoapAction.h"
#include <vector>
#include <deque>
#include <unordered_map>

class GoapNode;

class GoapPlanner
{
public:
	static std::deque<const GoapAction*> run(const std::unordered_map<std::string, bool>& agentState, const GoapAction& goal, const std::vector<const GoapAction*>& actions, const GoapAction& defaultAction);

private:
	static void removeAlreadySatisfiedPreconditions(GoapNode* node, const std::unordered_map<std::string, bool>& agentState);
	static bool isValid(GoapNode* node, std::unordered_map<std::string, bool> agentState, float& cost);
};
