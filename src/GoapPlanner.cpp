#include "GoapPlanner.h"
#include "GoapNode.h"
#include <algorithm>
#include <iterator>

std::deque<const GoapAction*> GoapPlanner::run(const std::unordered_map<std::string, bool>& agentState, const GoapAction& goal, const std::vector<const GoapAction*>& actions)
{
	GoapNode rootNode;
	rootNode.remainingPreconditions = goal.getPreconditions();
	rootNode.currentAction = &goal;
	
	std::transform(actions.begin(), actions.end(), std::back_inserter(rootNode.remainingActions), [](const GoapAction* action){
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
		
		for (const GoapAction* action : currentNode->remainingActions)
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
			
			
			if (childNode->remainingPreconditions.empty())
			{
				// Check if leaf is valid
				bool valid = true;
				float totalCost = 0;
				
				std::unordered_map<std::string, bool> simulatedAgentState = agentState;
				
				GoapNode* node = childNode;
				
				while (node->parent != nullptr && valid)
				{
					totalCost += node->currentAction->getCost();
					
					for (const auto& effect : node->currentAction->getEffects())
					{
						simulatedAgentState[effect.first] = effect.second;
					}
					
					for (const auto& precondition : node->parent->currentAction->getPreconditions())
					{
						if (simulatedAgentState[precondition.first] != precondition.second)
						{
							valid = false;
							break;
						}
					}
					
					node = node->parent;
				}
				
				if (valid && (bestNode == nullptr || totalCost < bestCost))
				{
					bestNode = childNode;
					bestCost = totalCost;
				}
			}
			else
			{
				openNodes.push_back(childNode);
			}
		}
	}
	
	if (bestNode != nullptr)
	{
		GoapNode* node = bestNode;
		std::deque<const GoapAction*> res;
		
		while (node != nullptr)
		{
			res.push_back(node->currentAction);
			node = node->parent;
		}
		
		return std::move(res);
	}
	else
	{
		return {};
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
