#pragma once

#include <vector>
#include <memory>
#include <deque>
#include "Action/GoapAction.h"
#include "Goap V1/World.h"

class GoapAgent
{
public:
	GoapAgent(std::string name, std::unique_ptr<GoapAction>&& goal, std::unique_ptr<GoapAction>&& defaultAction);
	void addState(std::string key, bool value);
	bool hasPlan();
	void addAction(std::unique_ptr<GoapAction>&& action);
	void makePlan();
	void performAction(World& world);
	
private:
	std::vector<std::unique_ptr<GoapAction>> _actions;
	std::unique_ptr<GoapAction> _goal;
	std::unique_ptr<GoapAction> _defaultAction;
	
	std::unordered_map<std::string, bool> _state;
	
	std::deque<const GoapAction*> _plan;

	std::string _name;
};
