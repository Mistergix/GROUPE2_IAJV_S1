#pragma once
#include <unordered_map>

#include "GoapAction.h"
class Node {
public :
	Node* parent;
	float cost;
	std::unordered_map<std::string, bool> state;
	std::unordered_map<std::string, bool> unfilledConditions;
	GoapAction* action;
	std::unordered_set<GoapAction> doableActions;

	Node() : cost(0), parent(), action() {}
	Node(Node& parent, float cost, std::unordered_map<std::string, bool>& state, std::unordered_map<std::string, bool>& unfilledConditions, std::unordered_set<GoapAction> doableActions, GoapAction action) : parent(parent), cost(cost), state(state), unfilledConditions(unfilledConditions), doableActions(doableActions),action(action) {}
	
	bool operator==(const Node& node) const;
	bool operator!=(const Node& node) const;
	bool operator==(const int& node) const;
	bool operator!=(const int& node) const;
	Node& operator=(const Node& node);
};