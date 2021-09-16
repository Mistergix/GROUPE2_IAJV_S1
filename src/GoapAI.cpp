#include "GoapAI.h"
#include <iostream>>
#include <limits>

bool IsIn(std::pair<const std::string, bool> data, std::unordered_map<std::string, bool>& map) {
	for (const auto& keyValue : map) {
		if (keyValue == data) {
			return true;
		}
	}

	return false;
}

void CreateUnFilledConditions(std::unordered_map<std::string, bool>& initialState, Node& node, std::unordered_map<std::string, bool>& unfilledConditions) {

	for (const auto& keyValue : node.unfilledConditions) {
		if (!IsIn(keyValue, node.action.effects)) {
			unfilledConditions[keyValue.first] = keyValue.second;
		}
	}
	for (const auto& keyValue : node.action->preConditions) {
		if (!IsIn(keyValue, initialState)) {
			unfilledConditions[keyValue.first] = keyValue.second;
		}
	}
}

bool GoapAI::IsValid(const Node& node) const{
	for (const auto& preCondition : node.action.preConditions) {
		if (!IsIn(preCondition, node.state)) {
			return false;
		}
	}

	for (const auto& preCondition : node.unfilledConditions) {
		if (!IsIn(preCondition, node.action.effects)) {
			return false;
		}
	}

	return true;
}

std::unordered_map<std::string, bool> UpdateState(std::unordered_map<std::string, bool> currentState, std::unordered_map<std::string, bool> effects)
{
	std::unordered_map<std::string, bool> state;
	// Copy Current State
	for (const auto& s : currentState) {
		state[s.first] = s.second;
	}

	// Apply Effects
	for (const auto& effect : effects) {
		state[effect.first] = effect.second;
	}


	return state;
}

int UnfilledConditionsCount(Node& node, std::unordered_map<std::string, bool>& unfilledConditions) {

}

std::unordered_set<GoapAction> GetSubset(std::unordered_set<GoapAction> actions, GoapAction& removeThisAction)
{
	std::unordered_set<GoapAction> subset;
	for (const auto& action : actions) {
		if (action != removeThisAction) {
			subset.insert(action);
		}
	}

	return subset;
}

bool GoapAI::BuildTree(std::vector<Node>& openNodes, std::vector<Node>& leaves, std::unordered_set<GoapAction> doableActions) {
	
	bool foundOneSolution = false;

	float currentBestCost = std::numeric_limits<float>::max();

	if (!leaves.empty()) {
		currentBestCost = BestNode(leaves)->cost;
	}

	for (const auto& node : openNodes) {
		if (IsValid(node)) {
			leaves.push_back(node);
			currentBestCost = BestNode(leaves)->cost;
			foundOneSolution = true;
		}
		else
		{
			std::vector<Node> newNodes;
			std::unordered_map<std::string, bool> currentState = UpdateState(node.state, node.action.effects);
			std::unordered_set<GoapAction> subset = GetSubset(doableActions, node.action);

			for (const auto& action : subset) {
				float cost = action.cost + node.cost;
				if (cost > currentBestCost) {
					// Skip because we already have a less expensive path
					continue;
				}

				std::unordered_map<std::string, bool> unfilledConditions;
				CreateUnFilledConditions(currentState, node, unfilledConditions);
				Node n(node, cost, currentState, unfilledConditions, subset, action);
				newNodes.push_back(node);
			}


			bool found = BuildTree(newNodes, leaves, subset);
			if (found) {
				foundOneSolution = found;
			}
		}
	}

	return foundOneSolution;
}

GoapAI::GoapAI()
{
	LoadActions();
}

void GoapAI::AddAction(GoapAction& action)
{
	 
}

void GoapAI::AddState(std::string key, bool value)
{
	initialState[key] = value;
	currentState[key] = value;
}

void GoapAI::PlanSequenceOfAction(std::unordered_map<std::string, bool>& goalState)
{
	PlanSequenceOfActions(currentState, goalState);
}

bool GoapAI::HasPlan()
{
	return hasPlan;
}

void GoapAI::PerformAction(World& world)
{
	if (currentActions.empty()) {
		hasPlan = false;
		return;
	}

	GoapAction& action = currentActions.front();
	if (action.Finished()) {
		UpdateEffects(action);
		currentActions.pop();
	}

	if (currentActions.empty()) {
		hasPlan = false;
		return;
	}

	action = currentActions.front();
	bool success = action.TryPerformAction(world);
	if (!success) {
		hasPlan = false;
		return;
	}
}

GoapAction* GoapAI::GetDefaultAction() {
	return defaultAction;
}

void GoapAI::SetDefaultAction(GoapAction* defaultAction)
{
	this->defaultAction = defaultAction;
}

Node* GoapAI::BestNode(std::vector<Node> leaves)
{
	Node bestNode;
	for (const auto& node : leaves) {
		if (bestNode == NULL || node.cost < bestNode.cost) {
			bestNode = node;
		}
	}

	return &bestNode;
}

void GoapAI::PlanSequenceOfActions(std::unordered_map<std::string, bool>& initialState, std::unordered_map<std::string, bool>& goalState)
{
	for (const auto& action : possibleActions) {
		action.Reset();
	}

	std::unordered_set<GoapAction> doableActions;

	for (const auto& action : possibleActions) {
		if (action.CanDoActionInContext(*this)) {
			doableActions.insert(action);
		}
	}

	std::vector<Node> openNodes;
	std::vector<Node> leaves;
	

	for (const auto& action : doableActions) {
		std::unordered_map<std::string, bool> unfilledConditions;
		CreateUnFilledConditions(initialState, goalState, unfilledConditions);
		for (const auto& effect : action.effects) {
			if (IsIn(effect, unfilledConditions)) {
				Node node(NULL, action.cost, initialState, unfilledConditions, doableActions, action);
				openNodes.push_back(node);
			}
		}
	}

	bool success = BuildTree(openNodes, leaves, doableActions);

	if (!success) {
		leaves.clear();
		GoapAction* action = GetDefaultAction();
		std::unordered_map<std::string, bool> unfilledConditions;
		Node node(NULL, action->cost, initialState, unfilledConditions, doableActions, action);
		leaves.push_back(node);
	}

	Node* bestNode = BestNode(leaves);

	currentActions = {}; // clear actions queue

	std::vector<GoapAction> actions;
	Node* n = bestNode;
	while (n != NULL) {
		if (n.action != NULL) {
			currentActions.push(n.action);
		}

		n = *n.parent;
	}

	std::cout << "We have a plan !!" << std::endl;
	hasPlan = true;
}

bool GoapAI::StateContainsTest(const std::unordered_map<std::string, bool>& test, std::unordered_map<std::string, bool>& state) const
{
	for (const auto& keyValue : test) {
		bool match = false;
		for (const auto& keyValueState : state) {
			if (keyValue == keyValueState) {
				match = true;
				break;
			}
		}
		if (!match) { return false; }
	}

	return true;
}

void GoapAI::UpdateEffects(GoapAction& action)
{
	currentState = UpdateState(currentState, action.effects);
}

