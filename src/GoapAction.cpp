#include "GoapAction.h"

GoapAction::GoapAction()
{
	GeneratePreConditions();
	GenerateEffects();
}

void GoapAction::AddPreCondition(std::string key, bool value)
{
	preConditions[key] = value;
}

void GoapAction::AddEffect(std::string key, bool value)
{
	effects[key] = value;
}

bool GoapAction::operator==(const GoapAction& goapA)
{
	return false;
}

bool GoapAction::operator==(const int& goapA)
{
	return cost == NULL && preConditions.empty() && effects.empty();
}

bool GoapAction::operator!=(const int& goapA)
{
	return cost != NULL && !preConditions.empty() && !effects.empty();
}

bool GoapAction::operator!=(const GoapAction &goapA) const
{
	return cost != goapA.cost && preConditions != goapA.preConditions && effects != goapA.effects;
}
