#include "GoapAction.h"
#include "GoapAI.h"

GoapAction::GoapAction(float cost, std::string name) : cost(cost), name(name)
{

}

void GoapAction::AddPreCondition(std::string key, bool value)
{
	preConditions[key] = value;
}

void GoapAction::AddEffect(std::string key, bool value)
{
	effects[key] = value;
}

std::string GoapAction::Name()
{
	return name;
}
