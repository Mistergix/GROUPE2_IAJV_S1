#include <algorithm>
#include <iterator>
#include "GoapAgent.h"
#include "GoapPlanner.h"
#include "Action/Action_AttackPlayer.h"
#include "Action/Action_MoveToPlayer.h"
#include "Action/Action_PickupWeapon.h"
#include "Action/Action_Reload.h"

GoapAgent::GoapAgent(std::string name):
_name(name)
{
	_goal = std::make_unique<Action_AttackPlayer>();
	
	_actions.push_back(std::make_unique<Action_MoveToPlayer>());
	_actions.push_back(std::make_unique<Action_PickupWeapon>());
	_actions.push_back(std::make_unique<Action_Reload>());
}

void GoapAgent::addState(std::string key, bool value)
{
	_state[key] = value;
}

void GoapAgent::makePlan()
{
	std::vector<const GoapAction*> actions;
	
	std::transform(_actions.begin(), _actions.end(), std::back_inserter(actions), [](const std::unique_ptr<GoapAction>& action){
		return action.get();
	});
	
	_plan = GoapPlanner::run(_state, *_goal, actions);
}
