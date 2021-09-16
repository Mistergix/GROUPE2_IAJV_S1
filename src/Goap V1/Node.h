#pragma once
#include <unordered_map>
#include <utility>

#include "GoapActionV1.h"

class Node {
public :
	Node* parent = nullptr;
	float cost;
	std::unordered_map<std::string, bool> state;
	std::unordered_map<std::string, bool> unfilledConditions;
	GoapActionV1* action = nullptr;
	std::list<GoapActionV1*> doableActions;
	Node() : cost(0.0f), parent(), action() {}
	Node(Node* parent, float cost, std::unordered_map<std::string, bool>& state, std::unordered_map<std::string, bool>& unfilledConditions, std::list<GoapActionV1*> doableActions, GoapActionV1* action) :
		parent(parent), cost(cost), state(state), unfilledConditions(unfilledConditions), doableActions(doableActions),action(action) {}
};