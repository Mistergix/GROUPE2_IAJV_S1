#pragma once

#include <vector>
#include <memory>
#include <deque>
#include "Action/GoapAction.h"

class GoapAgent
{
public:
	GoapAgent(std::string name, std::unique_ptr<GoapAction>&& goal, std::unique_ptr<GoapAction>&& defaultAction);
	void addState(std::string key, bool value);
	bool hasPlan();
	void addAction(std::unique_ptr<GoapAction>&& action);
	void makePlan();
	void performAction(WorldV2& world);
	void updateState(const GoapAction* action);
	std::unordered_map<std::string, bool> updateStateWithEffects(std::unordered_map<std::string, bool> state, const std::unordered_map<std::string, bool>& effects) const;
	std::string prettyPrint(std::unordered_map<std::string, bool> state);
	
private:
	std::vector<std::unique_ptr<GoapAction>> _actions;
	std::unique_ptr<GoapAction> _goal;
	std::unique_ptr<GoapAction> _defaultAction;
	
	std::unordered_map<std::string, bool> _state;
	
	std::deque<GoapAction*> _plan;

	std::string _name;
};
