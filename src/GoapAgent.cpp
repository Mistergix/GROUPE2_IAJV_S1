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
