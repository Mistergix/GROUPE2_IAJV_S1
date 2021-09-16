#pragma once

#include <unordered_map>

#include "../WorldV2.h"
class GoapAgent;

class GoapAction {
public:
	explicit GoapAction(float cost, std::string name);
	
	const std::unordered_map<std::string, bool>& getPreconditions() const;
	const std::unordered_map<std::string, bool>& getEffects() const;
	
	float getCost() const;
	
	const std::string& getName() const;

	virtual bool tryPerformAction(WorldV2& world, GoapAgent& ai) = 0;
	virtual bool finished() const = 0;
	virtual bool canDoActionInContext(WorldV2& world, GoapAgent& ai) const = 0;
	virtual void reset() = 0;

protected:
	void addPrecondition(const std::string& key, bool value);
	void addEffect(const std::string& key, bool value);
	
	std::string _name;

private:
	std::unordered_map<std::string, bool> _preconditions;
	std::unordered_map<std::string, bool> _effects;
	float _cost;
};