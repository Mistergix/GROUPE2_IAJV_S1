#pragma once

#include "GoapAction.h"

class Action_MoveToPlayer : public GoapAction
{
public:
	Action_MoveToPlayer();
	virtual bool tryPerformAction(WorldV2& world, GoapAgent& ai) override;
	virtual bool finished() const override;
	virtual bool canDoActionInContext(WorldV2& world, GoapAgent& ai) const override;
	virtual void reset() override;
private :
	float timeToMove;
	float currentTimeToMove;
};
