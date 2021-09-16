#pragma once
#include <unordered_map>

#include "World.h"
class GoapAI;

class GoapActionV1 {
public:
	explicit GoapActionV1(float cost, std::string name);
	virtual bool TryPerformAction(World& world, GoapAI& ai) = 0;
	virtual bool Finished() const = 0;
	virtual bool CanDoActionInContext(World& world, GoapAI& ai) const = 0;
	virtual void Reset() = 0;
	void AddPreCondition(std::string key, bool value);
	void AddEffect(std::string key, bool value);
	std::unordered_map<std::string, bool> preConditions;
	std::unordered_map<std::string, bool> effects;
	float cost;
	std::string Name();
private :
	std::string name;
};