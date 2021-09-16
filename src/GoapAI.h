#pragma once
#include <unordered_set>
#include <queue>

#include "Node.h"
#include "GoapAction.h"
#include "World.h"

class GoapAI {
public:
	GoapAI();
	virtual void LoadActions() = 0; // protected in c++ ?
	void AddAction(GoapAction& action);
	void AddState(std::string key, bool value);
	void PlanSequenceOfAction(std::unordered_map<std::string, bool>& goalState);
	bool HasPlan();
	void PerformAction(World& world);
	GoapAction* GetDefaultAction();
	void SetDefaultAction(GoapAction* defaultAction);
	Node* BestNode(std::vector<Node> leaves);
private :
	std::vector<GoapAction> _possibleActions;
	std::queue<GoapAction*> _currentActions;
	std::unordered_map<std::string, bool> _currentState;;
	bool _hasPlan;
	GoapAction* defaultAction;

	void PlanSequenceOfActions(std::unordered_map<std::string, bool>& initialState, std::unordered_map<std::string, bool>& goalState);
	static bool StateContainsTest(std::unordered_map<std::string, bool>& test, std::unordered_map<std::string, bool>& state);
	void UpdateEffects(GoapAction& action);
	static std::unordered_map<std::string, bool> UpdateState(std::unordered_map<std::string, bool> state, std::unordered_map<std::string, bool>& effects);
	bool IsValid(const Node& node) const;
	static std::vector<GoapAction*> GetSubset(std::vector<GoapAction*> actions, GoapAction* removeThisAction);
	bool BuildTree(std::vector<Node>& openNodes, std::vector<Node>& leaves, std::vector<GoapAction*>& doableActions);
	static bool IsIn(const std::pair<const std::string, bool>& data, const std::unordered_map<std::string, bool>& map);
	void CreateUnFilledConditions(std::unordered_map<std::string, bool>& initialState, Node& node, std::unordered_map<std::string, bool>& unfilledConditions);
	void CreateInitialUnFilledConditions(std::unordered_map<std::string, bool>& initialState, std::unordered_map<std::string, bool>& goalState, std::unordered_map<std::string, bool>& unfilledConditions);
};