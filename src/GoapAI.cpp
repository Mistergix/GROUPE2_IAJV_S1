#include "GoapAI.h"
#include <iostream>>

GoapAI::GoapAI()
{
	LoadActions();
}

void GoapAI::AddAction(GoapAction& action)
{
	possibleActions.insert(action);
}

void GoapAI::AddState(std::string key, bool value)
{
	initialState[key] = value;
}

void GoapAI::PlanSequenceOfAction(std::unordered_map<std::string, bool>& goalState)
{
	PlanSequenceOfActions(initialState, goalState);
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

void GoapAI::PlanSequenceOfActions(std::unordered_map<std::string, bool>& initialState, std::unordered_map<std::string, bool>& goalState)
{
	for (const auto& action : possibleActions) {
		action.Reset();
	}

	std::unordered_set<GoapAction> doableActions;

	for (const auto& action : possibleActions) {
		if (action.CanDoAction(*this)) {
			doableActions.insert(action);
		}
	}

	std::vector<Node> leaves;

	Node* nullParent;
	GoapAction* nullAction;
	Node start(nullParent, 0.0f, initialState, *nullAction);
	bool success = BuildTree(start, leaves, doableActions, goalState);

	if (!success) {
		std::cout << "Failed To Create Plan" << std::endl;
		hasPlan = false;
		return;
	}

	Node bestNode;
	for (const auto& node : leaves) {
		if (bestNode == NULL || node.cost < bestNode.cost) {
			bestNode = node;
		}
	}

	currentActions = {}; // clear actions queue

	std::vector<GoapAction> actions;
	Node n = bestNode;
	while (n != NULL) {
		if (n.action != NULL) {
			auto itPos = actions.begin();
			GoapAction* action = n.action;
			actions.insert(itPos, *action);
		}

		n = *n.parent;
	}

	for (const auto& action : actions) {
		currentActions.push(action);
	}

	std::cout << "We have a plan !!" << std::endl;
	hasPlan = true;
}

bool GoapAI::BuildTree(Node& parent, std::vector<Node>& leaves, std::unordered_set<GoapAction> doableActions, std::unordered_map<std::string, bool>& goalState)
{
	bool foundOneSolution = false;

	for (const auto& action : doableActions) {
		if (StateContainsTest(action.preConditions, parent.state)) {
			std::unordered_map<std::string, bool> currentState = UpdateState(parent.state, action.effects);
			Node node(&parent, parent.cost + action.cost, currentState, action);
			if (StateContainsTest(goalState, currentState)) {
				leaves.push_back(node);
				foundOneSolution = true;
			}
			else
			{
				std::unordered_set<GoapAction> subset = GetSubset(doableActions, action);
				bool found = BuildTree(node, leaves, subset, goalState);
				if (found) {
					foundOneSolution = found;
				}
			}
		}
	}

	return foundOneSolution;
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

std::unordered_map<std::string, bool> GoapAI::UpdateState(std::unordered_map<std::string, bool> currentState, std::unordered_map<std::string, bool> effects)
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

std::unordered_set<GoapAction> GoapAI::GetSubset(std::unordered_set<GoapAction> actions, const GoapAction& removeThisAction) const
{
	std::unordered_set<GoapAction> subset;
	for (const auto& action : actions) {
		if (action != removeThisAction) {
			subset.insert(action);
		}
	}

	return subset;
}

