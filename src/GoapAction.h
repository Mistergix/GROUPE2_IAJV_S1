#pragma once
#include <unordered_map>

#include "World.h"
class GoapAI;

class GoapAction {
public:
	GoapAction(float cost);
	virtual void GeneratePreConditions() = 0;
	virtual void GenerateEffects() = 0;
	virtual bool TryPerformAction(World world) = 0;
	virtual bool Finished() = 0;
	virtual bool CanDoActionInContext(GoapAI& ai) const = 0;
	virtual void Reset() = 0;
	void AddPreCondition(std::string key, bool value);
	void AddEffect(std::string key, bool value);
	std::unordered_map<std::string, bool> preConditions;
	std::unordered_map<std::string, bool> effects;
	float cost;
};