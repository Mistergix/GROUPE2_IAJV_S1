#pragma once

#include "Action/GoapAction.h"
#include <vector>
#include <deque>
#include <unordered_map>

class GoapNode;

class GoapPlanner
{
public:
	static std::deque<GoapAction*> run(const std::unordered_map<std::string, bool>& agentState, GoapAction& goal, const std::vector<GoapAction*>& actions, GoapAction& defaultAction);

private:
	static void removeAlreadySatisfiedPreconditions(GoapNode* node, const std::unordered_map<std::string, bool>& agentState);
	static bool isValid(GoapNode* node, std::unordered_map<std::string, bool> agentState, float& cost);
	static std::string prettyPrint(GoapNode& node);
};
