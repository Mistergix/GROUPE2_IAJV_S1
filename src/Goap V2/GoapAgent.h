#pragma once

#include <vector>
#include <memory>
#include <deque>
#include "Action/GoapAction.h"

class GoapAgent
{
public:
	GoapAgent();
	
	void makePlan();
	
private:
	std::vector<std::unique_ptr<GoapAction>> _actions;
	std::unique_ptr<GoapAction> _goal;
	
	std::unordered_map<std::string, bool> _state;
	
	std::deque<const GoapAction*> _plan;
};
