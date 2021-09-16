#include "GoapAction.h"
#include "GoapAI.h"

GoapAction::GoapAction(float cost) : cost(cost)
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
