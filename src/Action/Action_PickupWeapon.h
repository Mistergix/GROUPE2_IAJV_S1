#pragma once

#include "GoapAction.h"

class Action_PickupWeapon : public GoapAction
{
public:
	Action_PickupWeapon(float time);
	virtual bool tryPerformAction(WorldV2& world, GoapAgent& ai) override;
	virtual bool finished() const override;
	virtual bool canDoActionInContext(WorldV2& world, GoapAgent& ai) const override;
	virtual void reset() override;
private:
	//TODO Refactor this, we figured we need this in almost any GoapAction
	float timeToGetWeapon;
	float currentTimeToGetWeapon;
};
