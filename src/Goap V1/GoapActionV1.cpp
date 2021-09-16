#include "GoapActionV1.h"
#include "GoapAI.h"

GoapActionV1::GoapActionV1(float cost, std::string name) : cost(cost), name(name)
{

}

void GoapActionV1::AddPreCondition(std::string key, bool value)
{
	preConditions[key] = value;
}

void GoapActionV1::AddEffect(std::string key, bool value)
{
	effects[key] = value;
}

std::string GoapActionV1::Name()
{
	return name;
}
