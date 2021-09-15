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
private :
	std::unordered_set<GoapAction> possibleActions;
	std::queue<GoapAction> currentActions;
	std::unordered_map<std::string, bool> initialState;
	std::unordered_map<std::string, bool> currentState;
	bool hasPlan;

	void PlanSequenceOfActions(std::unordered_map<std::string, bool>& initialState, std::unordered_map<std::string, bool>& goalState);
	bool StateContainsTest(std::unordered_map<std::string, bool>& test, std::unordered_map<std::string, bool>& state);
	void UpdateEffects(GoapAction& action);
	std::unordered_map<std::string, bool> UpdateState(std::unordered_map<std::string, bool> currentState, std::unordered_map<std::string, bool> effects);
	std::unordered_set<GoapAction> GetSubset(std::unordered_set<GoapAction> actions, GoapAction& removeThisAction);
};