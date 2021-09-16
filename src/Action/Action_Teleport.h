#pragma once

#include "GoapAction.h"

class Action_Teleport : public GoapAction
{
public:
	Action_Teleport();
	virtual bool tryPerformAction(WorldV2& world, GoapAgent& ai) override;
	virtual bool finished() const override;
	virtual bool canDoActionInContext(WorldV2& world, GoapAgent& ai) const override;
	virtual void reset() override;
private:
	float reloadTime;
	float currentReloadTime;
	bool _finished;
};
