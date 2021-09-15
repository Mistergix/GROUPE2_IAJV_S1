#pragma once
#include <unordered_map>

#include "GoapAction.h"
class Node {
public :
	Node* parent;
	float cost;
	std::unordered_map<std::string, bool> state;
	GoapAction* action;

	Node() : cost(0), parent(), action(){}
	Node(Node* parent, float cost, std::unordered_map<std::string, bool> state, GoapAction action) : parent(parent), cost(cost), state(state), action(&action) {}
	bool operator==(const Node& node) const;
	bool operator!=(const Node& node) const;
	bool operator==(const int& node) const;
	bool operator!=(const int& node) const;
	Node& operator=(const Node& node);
};