#pragma once
#include <unordered_map>
#include <utility>

#include "GoapAction.h"

class Node {
public :
	Node* parent;
	float cost;
	std::unordered_map<std::string, bool> state;
	std::unordered_map<std::string, bool> unfilledConditions;
	GoapAction* action;
	std::vector<GoapAction*> doableActions;
	Node() : cost(0.0f), parent(), action() {}
	Node(Node* parent, float cost, std::unordered_map<std::string, bool>& state, std::unordered_map<std::string, bool>& unfilledConditions, std::vector<GoapAction*> doableActions, GoapAction* action) : parent(parent), cost(cost), state(state), unfilledConditions(unfilledConditions), doableActions(std::move(doableActions)),action(action) {}
};