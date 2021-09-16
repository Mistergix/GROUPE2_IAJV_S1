#include "GoapAction.h"

GoapAction::GoapAction(float cost, std::string name):
_cost(cost), _name(std::move(name))
{

}

void GoapAction::addPrecondition(const std::string& key, bool value)
{
	_preconditions[key] = value;
}

void GoapAction::addEffect(const std::string& key, bool value)
{
	_effects[key] = value;
}

const std::unordered_map<std::string, bool>& GoapAction::getPreconditions() const
{
	return _preconditions;
}

const std::unordered_map<std::string, bool>& GoapAction::getEffects() const
{
	return _effects;
}

float GoapAction::getCost() const
{
	return _cost;
}

const std::string& GoapAction::getName() const
{
	return _name;
}
