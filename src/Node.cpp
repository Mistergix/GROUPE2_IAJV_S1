#include "Node.h"

bool Node::operator==(const Node& node) const
{
	return cost == node.cost && parent == node.parent && action == node.action;
}

bool Node::operator!=(const Node& node) const
{
	return cost != node.cost && parent != node.parent && action != node.action;
}

bool Node::operator==(const int& node) const
{
	return parent == NULL && action == NULL;
}


bool Node::operator!=(const int& node) const
{
	return true;
}

Node& Node::operator=(const Node& node)
{
	return *this;
}

