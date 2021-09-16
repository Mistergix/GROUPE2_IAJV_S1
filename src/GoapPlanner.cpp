#include "GoapPlanner.h"
#include "GoapNode.h"
#include <algorithm>
#include <iterator>
#include <iostream>
#include <format>

std::deque<GoapAction*> GoapPlanner::run(const std::unordered_map<std::string, bool>& agentState, GoapAction& goal, const std::vector<GoapAction*>& actions, GoapAction& defaultAction)
{
	GoapNode rootNode;
	rootNode.remainingPreconditions = goal.getPreconditions();
	rootNode.currentAction = &goal;
	
	std::transform(actions.begin(), actions.end(), std::back_inserter(rootNode.remainingActions), [](GoapAction* action){
		return action;
	});
	
	removeAlreadySatisfiedPreconditions(&rootNode, agentState);
	
	std::list<GoapNode*> openNodes;
	
	GoapNode* bestNode = nullptr;
	float bestCost = -1;
	
	openNodes.push_back(&rootNode);
	
	while (!openNodes.empty())
	{
		uint64_t lowestPreconditionCount = openNodes.front()->remainingPreconditions.size();
		
		for (GoapNode* node : openNodes)
		{
			lowestPreconditionCount = std::min(node->remainingPreconditions.size(), lowestPreconditionCount);
		}
		
		GoapNode* currentNode;
		
		for (auto it = openNodes.begin(); it != openNodes.end(); it++)
		{
			if ((*it)->remainingPreconditions.size() == lowestPreconditionCount)
			{
				currentNode = *it;
				openNodes.erase(it);
				break;
			}
		}
		
		if (currentNode->remainingPreconditions.empty())
		{
			// Check if leaf is valid
			
			float cost;
			
			if (isValid(currentNode, agentState, cost) && (bestNode == nullptr || cost < bestCost))
			{
				bestNode = currentNode;
				bestCost = cost;
			}
		}
		else
		{
			for (GoapAction* action : currentNode->remainingActions)
			{
				GoapNode* childNode = &currentNode->children.emplace_back();
				childNode->parent = currentNode;
				
				childNode->remainingPreconditions = currentNode->remainingPreconditions;
				childNode->remainingActions = currentNode->remainingActions;
				
				childNode->remainingActions.erase(
					std::find(childNode->remainingActions.begin(), childNode->remainingActions.end(), action)
				);
				childNode->currentAction = action;
				
				// Apply effects to preconditions
				for (const auto& effect : action->getEffects())
				{
					auto matchingPreconditionIt = childNode->remainingPreconditions.find(effect.first);
					if (matchingPreconditionIt != childNode->remainingPreconditions.end() && matchingPreconditionIt->second == effect.second)
					{
						childNode->remainingPreconditions.erase(matchingPreconditionIt);
					}
				}
				
				// Add new preconditions from added action
				for (const auto& addedPrecondition : action->getPreconditions())
				{
					childNode->remainingPreconditions.insert(addedPrecondition);
				}
				
				removeAlreadySatisfiedPreconditions(childNode, agentState);
				
				
				openNodes.push_back(childNode);
			}
		}
	}
	
	if (bestNode != nullptr)
	{
		GoapNode* node = bestNode;
		std::deque<GoapAction*> res;
		
		while (node != nullptr)
		{
			res.push_back(node->currentAction);
			node = node->parent;
		}

		std::cout << " Finished Planning, the plan is : " << std::endl;
		std::cout << prettyPrint(*bestNode);
		
		return std::move(res);
	}
	else
	{
		std::cout << "NO PATH FOUND, DEFAULT PATH" << std::endl;
		return {
			&defaultAction
		};
	}
}

void GoapPlanner::removeAlreadySatisfiedPreconditions(GoapNode* node, const std::unordered_map<std::string, bool>& agentState)
{
	for (auto it = node->remainingPreconditions.begin(); it != node->remainingPreconditions.end();)
	{
		if (agentState.at(it->first) == it->second)
		{
			it = node->remainingPreconditions.erase(it);
		}
		else
		{
			it++;
		}
	}
}

bool GoapPlanner::isValid(GoapNode* node, std::unordered_map<std::string, bool> agentState, float& cost)
{
	bool valid = true;
	float totalCost = 0;
	
	while (node->parent != nullptr && valid)
	{
		totalCost += node->currentAction->getCost();
		
		for (const auto& effect : node->currentAction->getEffects())
		{
			agentState[effect.first] = effect.second;
		}
		
		for (const auto& precondition : node->parent->currentAction->getPreconditions())
		{
			if (agentState[precondition.first] != precondition.second)
			{
				valid = false;
				break;
			}
		}
		
		node = node->parent;
	}
	
	if (valid)
	{
		cost = totalCost;
	}
	
	return valid;
}

std::string GoapPlanner::prettyPrint(GoapNode& node)
{
	std::string s = "";
	GoapNode* n = &node;
	while (n != nullptr) {
		if (n->currentAction != nullptr) {
			s += std::format("{} ({}) -> ", n->currentAction->getName(), n->currentAction->getCost());
		}

		n = n->parent;
	}
	s += "GOAL";
	return s;
}