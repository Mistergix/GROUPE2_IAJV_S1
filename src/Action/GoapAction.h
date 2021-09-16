#pragma once

#include <unordered_map>

class GoapAction {
public:
	explicit GoapAction(float cost, std::string name);
	
	const std::unordered_map<std::string, bool>& getPreconditions() const;
	const std::unordered_map<std::string, bool>& getEffects() const;
	
	float getCost() const;
	
	const std::string& getName() const;

protected:
	void addPrecondition(const std::string& key, bool value);
	void addEffect(const std::string& key, bool value);
	
	std::string _name;

private:
	std::unordered_map<std::string, bool> _preconditions;
	std::unordered_map<std::string, bool> _effects;
	float _cost;
};