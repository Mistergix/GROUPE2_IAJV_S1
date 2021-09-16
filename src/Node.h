#pragma once
#include <unordered_map>
#include <utility>

#include "GoapAction.h"

class Node {
public :
	Node* parent = nullptr;
	float cost;
	std::unordered_map<std::string, bool> state;
	std::unordered_map<std::string, bool> unfilledConditions;
	GoapAction* action = nullptr;
	std::list<GoapAction*> doableActions;
	Node() : cost(0.0f), parent(), action() {}
	Node(Node* parent, float cost, std::unordered_map<std::string, bool>& state, std::unordered_map<std::string, bool>& unfilledConditions, std::list<GoapAction*> doableActions, GoapAction* action) : 
		parent(parent), cost(cost), state(state), unfilledConditions(unfilledConditions), doableActions(doableActions),action(action) {}
};