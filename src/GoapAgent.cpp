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
	std::cout << _name << " IS PLANNING ..." << std::endl;
	std::vector<const GoapAction*> actions;
	
	std::transform(_actions.begin(), _actions.end(), std::back_inserter(actions), [](const std::unique_ptr<GoapAction>& action){
		return action.get();
	});
	
	_plan = GoapPlanner::run(_state, *_goal, actions, *_defaultAction);
	std::cout << "---------------------------------------------------" << std::endl << std::endl;
}

void GoapAgent::performAction(World& world)
{
	std::cout << _name << " IS Performing Action ..." << std::endl;
	if (!hasPlan()) {
		std::cout << "No more actions ..." << std::endl;
		return;
	}

	GoapAction* action = _plan.front();
	if (action->finished()) {
		std::cout << action->getName() + " is finished !" << std::endl;
		UpdateEffects(action);
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
