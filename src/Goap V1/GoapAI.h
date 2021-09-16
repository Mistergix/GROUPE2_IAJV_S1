#pragma once
#include <unordered_set>
#include <queue>

#include "Node.h"
#include "GoapActionV1.h"
#include "World.h"

class GoapAI {
public:
	GoapAI(std::string name);
	void AddAction(GoapActionV1& action);
	void AddState(std::string key, bool value);
	void PlanSequenceOfAction(std::unordered_map<std::string, bool>& goalState, World& world);
	bool HasPlan();
	void PerformAction(World& world);
	GoapActionV1* GetDefaultAction();
	void SetDefaultAction(GoapActionV1* defaultAction);
	Node* BestNode(std::list<Node> leaves);
	std::string PrettyPrint(Node& node);
	std::string PrettyPrint(std::unordered_map<std::string, bool> state);
private :
	std::list<GoapActionV1*> _possibleActions;
	std::queue<GoapActionV1*> _currentActions;
	std::unordered_map<std::string, bool> _currentState;;
	bool _hasPlan;
	GoapActionV1* defaultAction;
	std::string name;

	void PlanSequenceOfActions(std::unordered_map<std::string, bool>& initialState, std::unordered_map<std::string, bool>& goalState, World& world);
	static bool StateContainsTest(std::unordered_map<std::string, bool>& test, std::unordered_map<std::string, bool>& state);
	void UpdateEffects(GoapActionV1& action);
	static std::unordered_map<std::string, bool> UpdateState(std::unordered_map<std::string, bool> state, std::unordered_map<std::string, bool>& effects);
	bool IsValid(const Node& node) const;
	static std::list<GoapActionV1*> GetSubset(std::list<GoapActionV1*> actions, GoapActionV1* removeThisAction);
	bool BuildTree(std::list<Node>& openNodes, std::list<Node>& leaves, std::list<GoapActionV1*>& doableActions);
	static bool IsIn(const std::pair<const std::string, bool>& data, const std::unordered_map<std::string, bool>& map);
	void CreateUnFilledConditions(std::unordered_map<std::string, bool>& initialState, Node& node, std::unordered_map<std::string, bool>& unfilledConditions);
	void CreateInitialUnFilledConditions(std::unordered_map<std::string, bool>& initialState, std::unordered_map<std::string, bool>& goalState, std::unordered_map<std::string, bool>& unfilledConditions);
};