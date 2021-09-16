#include "GoapAI.h"
#include <iostream>
#include <limits>

bool GoapAI::IsIn(const std::pair<const std::string, bool>& data, const std::unordered_map<std::string, bool>& map) {
	for (const auto& keyValue : map) {
		if (keyValue == data) {
			return true;
		}
	}

	return false;
}

void GoapAI::CreateUnFilledConditions(std::unordered_map<std::string, bool>& initialState, Node& node, std::unordered_map<std::string, bool>& unfilledConditions) {

	for (const auto& keyValue : node.unfilledConditions) {
		if (!IsIn(keyValue, node.action->effects)) {
			unfilledConditions[keyValue.first] = keyValue.second;
		}
	}
	for (const auto& keyValue : node.action->preConditions) {
		if (!IsIn(keyValue, initialState)) {
			unfilledConditions[keyValue.first] = keyValue.second;
		}
	}
}

void GoapAI::CreateInitialUnFilledConditions(std::unordered_map<std::string, bool>& initialState, std::unordered_map<std::string, bool>& goalState, std::unordered_map<std::string, bool>& unfilledConditions)
{
	for (const auto& keyValue : goalState) {
		if (!IsIn(keyValue, initialState)) {
			unfilledConditions[keyValue.first] = keyValue.second;
		}
	}
}

bool GoapAI::IsValid(const Node& node) const {
	for (const auto& preCondition : node.action->preConditions) {
		if (!IsIn(preCondition, node.state)) {
			return false;
		}
	}

	for (const auto& preCondition : node.unfilledConditions) {
		if (!IsIn(preCondition, node.action->effects)) {
			return false;
		}
	}

	return true;
}

std::unordered_map<std::string, bool> GoapAI::UpdateState(std::unordered_map<std::string, bool> state, std::unordered_map<std::string, bool>& effects)
{
	// Apply Effects
	for (const auto& effect : effects) {
		state[effect.first] = effect.second;
	}

	return state;
}

std::list<GoapActionV1*> GoapAI::GetSubset(std::list<GoapActionV1*> actions, GoapActionV1* removeThisAction)
{
	auto it = std::find(actions.begin(), actions.end(), removeThisAction);
	if (it != actions.end())
	{
		actions.erase(it);
	}

	return actions;
}

bool GoapAI::BuildTree(std::list<Node>& openNodes, std::list<Node>& leaves, std::list<GoapActionV1*>& doableActions) {
	
	bool foundOneSolution = false;

	float currentBestCost = std::numeric_limits<float>::max();

	if (!leaves.empty()) {
		currentBestCost = BestNode(leaves)->cost;
	}

	for (auto& node : openNodes) {
		if (IsValid(node)) {
			leaves.push_back(node);
			currentBestCost = BestNode(leaves)->cost;
			foundOneSolution = true;
		}
		else
		{
			std::list<Node> newNodes;
			std::unordered_map<std::string, bool> currentState = UpdateState(node.state, node.action->effects);
			std::list<GoapActionV1*> subset = GetSubset(doableActions, node.action);

			for (const auto& action : subset) {
				float cost = action->cost + node.cost;
				if (cost > currentBestCost) {
					// Skip because we already have a less expensive path
					continue;
				}

				std::unordered_map<std::string, bool> unfilledConditions;
				CreateUnFilledConditions(currentState, node, unfilledConditions);
				Node n(&node, cost, currentState, unfilledConditions, subset, action);
				newNodes.push_back(n);
			}


			bool found = BuildTree(newNodes, leaves, subset);
			if (found) {
				foundOneSolution = found;
			}
		}
	}

	return foundOneSolution;
}

GoapAI::GoapAI(std::string name) : name(name)
{
	_hasPlan = false;
}

void GoapAI::AddAction(GoapActionV1& action)
{
	_possibleActions.push_back(&action);
}

void GoapAI::AddState(std::string key, bool value)
{
	_currentState[key] = value;
}

void GoapAI::PlanSequenceOfAction(std::unordered_map<std::string, bool>& goalState, World& world)
{
	std::cout << name << " IS PLANNING ..." << std::endl;
	PlanSequenceOfActions(_currentState, goalState, world);
	
	std::cout << "---------------------------------------------------" << std::endl << std::endl;
}

bool GoapAI::HasPlan()
{
	return _hasPlan;
}

void GoapAI::PerformAction(World& world)
{
	std::cout << name << " IS Performing Action ..." << std::endl;
	if (_currentActions.empty()) {
		std::cout << "No more actions ..." << std::endl;
		_hasPlan = false;
		return;
	}

	GoapActionV1& action = *(_currentActions.front());
	if (action.Finished()) {
		std::cout << action.Name() + " is finished !" << std::endl;
		UpdateEffects(action);
		_currentActions.pop();
	}

	if (_currentActions.empty()) {
		std::cout << "No more actions ..." << std::endl;
		_hasPlan = false;
		return;
	}

	action = *(_currentActions.front());
	std::cout << "Current Action is " + action.Name() << std::endl;
	bool success = action.TryPerformAction(world, *this);
	if (!success) {
		std::cout << "Failed to perform action, need a new plan" << std::endl;
		_hasPlan = false;
		return;
	}
}

GoapActionV1* GoapAI::GetDefaultAction() {
	return defaultAction;
}

void GoapAI::SetDefaultAction(GoapActionV1* defaultAction)
{
	this->defaultAction = defaultAction;
}

Node* GoapAI::BestNode(std::list<Node> leaves)
{
	Node bestNode;
	for (const auto& node : leaves) {
		if (&bestNode == nullptr || node.cost < bestNode.cost) {
			bestNode = node;
		}
	}

	return &bestNode;
}

std::string GoapAI::PrettyPrint(Node& node)
{
	std::string s = "";
	Node* n = &node;
	while (n != nullptr) {
		if (n->action != nullptr) {
			s += n->action->Name();
			s += " (";
			s += n->action->cost;
			s += ") -> ";
		}

		n = n->parent;
	}
	s += "GOAL";
	return s;
}

std::string GoapAI::PrettyPrint(std::unordered_map<std::string, bool> state)
{
	std::string s = "[ ";
	for (const auto& pair : state) {
		s += pair.first + " = " + (pair.second ? "T" : "F");
		s += ",";
	}
	s += " ]";
	return s;
}

void GoapAI::PlanSequenceOfActions(std::unordered_map<std::string, bool>& initialState, std::unordered_map<std::string, bool>& goalState, World& world)
{
	for (auto& action : _possibleActions) {
		action->Reset();
	}

	std::list<GoapActionV1*> doableActions;

	for (auto& action : _possibleActions) {
		if (action->CanDoActionInContext(world, *this)) {
			doableActions.push_back(action);
		}
	}

	std::list<Node> openNodes;
	std::list<Node> leaves;
	

	for (const auto& action : doableActions) {
		std::unordered_map<std::string, bool> unfilledConditions;
		std::unordered_map<std::string, bool> temp;
		CreateInitialUnFilledConditions(initialState, goalState, unfilledConditions);
		for (const auto& effect : action->effects) {
			if (IsIn(effect, unfilledConditions)) {
				Node node(nullptr, action->cost, initialState, unfilledConditions, doableActions, action);
				openNodes.push_back(node);
			}
		}
	}

	bool success = BuildTree(openNodes, leaves, doableActions);

	if (!success) {
		std::cout << "NO PATH FOUND, DEFAULT PATH";
		leaves.clear();
		GoapActionV1* action = GetDefaultAction();
		std::unordered_map<std::string, bool> unfilledConditions;
		Node node(nullptr, action->cost, initialState, unfilledConditions, doableActions, action);
		leaves.push_back(node);
	}

	std::cout << " All the paths are " << std::endl;
	for (auto& leaf : leaves) {
		PrettyPrint(leaf);
	}

	Node* bestNode = BestNode(leaves);

	_currentActions = {}; // clear actions queue

	std::vector<GoapActionV1> actions;
	Node* n = bestNode;
	while (n != nullptr) {
		if (n->action != nullptr) {
			_currentActions.push(n->action);
		}

		n = n->parent;
	}

	std::cout << " Finished Planning, the plan is : " << std::endl;
	std::cout << PrettyPrint(*bestNode);
	_hasPlan = true;
}

bool GoapAI::StateContainsTest(std::unordered_map<std::string, bool>& test, std::unordered_map<std::string, bool>& state)
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

void GoapAI::UpdateEffects(GoapActionV1& action)
{
	std::cout << "OLD State is " << PrettyPrint(_currentState);
	_currentState = UpdateState(_currentState, action.effects);
	std::cout << "NEW State is " << PrettyPrint(_currentState);
}

