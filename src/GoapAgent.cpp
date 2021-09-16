#include <algorithm>
#include <iterator>
#include "GoapAgent.h"
#include "GoapPlanner.h"
#include <iostream>


GoapAgent::GoapAgent(std::string name, std::unique_ptr<GoapAction>&& goal, std::unique_ptr<GoapAction>&& defaultAction) :
_name(name),
_defaultAction(std::move(defaultAction)),
_goal(std::move(goal))
{
}

void GoapAgent::addState(std::string key, bool value)
{
	_state[key] = value;
}

bool GoapAgent::hasPlan()
{
	return ! _plan.empty();
}


void GoapAgent::addAction(std::unique_ptr<GoapAction>&& action) {
	_actions.push_back(std::move(action));
}

void GoapAgent::makePlan()
{
	std::cout << std::endl << std::endl;
	std::cout << _name << " IS PLANNING ..." << std::endl;
	std::vector<GoapAction*> actions;
	
	std::transform(_actions.begin(), _actions.end(), std::back_inserter(actions), [](std::unique_ptr<GoapAction>& action){
		return action.get();
	});

	_goal->reset();

	for (auto& action : actions) {
		action->reset();
	}

	std::cout << "Current state is " << prettyPrint(_state) << std::endl;
	
	_plan = GoapPlanner::run(_state, *_goal, actions, *_defaultAction);



	std::cout << "---------------------------------------------------" << std::endl << std::endl;
}

void GoapAgent::performAction(WorldV2& world)
{
	std::cout << _name << " IS Performing Action ..." << std::endl;
	if (!hasPlan()) {
		std::cout << "No more actions ..." << std::endl;
		return;
	}

	GoapAction* action = _plan.front();
	if (action->finished()) {
		std::cout << action->getName() + " is finished !" << std::endl;
		updateState(action);
		_plan.pop_front();
	}

	if (!hasPlan()) {
		std::cout << "No more actions ..." << std::endl;
		return;
	}

	action = _plan.front();
	std::cout << "Current Action is " + action->getName() << std::endl;
	bool success = action->tryPerformAction(world, *this);
	if (!success) {
		std::cout << "Failed to perform action, need a new plan" << std::endl;
		_plan = {};
		return;
	}
}

std::string GoapAgent::prettyPrint(std::unordered_map<std::string, bool> state)
{
	std::string s = "[ ";
	for (const auto& pair : state) {
		s += pair.first + " = " + (pair.second ? "true" : "false");
		s += ", ";
	}
	s += " ]";
	s += '\n';
	return s;
}

void GoapAgent::updateState(const GoapAction* action)
{
	std::cout << "OLD State is " << prettyPrint(_state);
	_state = updateStateWithEffects(_state, action->getEffects());
	std::cout << "NEW State is " << prettyPrint(_state);
}

std::unordered_map<std::string, bool> GoapAgent::updateStateWithEffects(std::unordered_map<std::string, bool> state, const std::unordered_map<std::string, bool>& effects) const
{
	// Apply Effects
	for (const auto& effect : effects) {
		state[effect.first] = effect.second;
	}

	return state;
}
