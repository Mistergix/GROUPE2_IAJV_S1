#pragma once

#include "GoapAction.h"

class Action_Reload : public GoapAction
{
public:
	Action_Reload();
	virtual bool tryPerformAction(WorldV2& world, GoapAgent& ai) override;
	virtual bool finished() const override;
	virtual bool canDoActionInContext(WorldV2& world, GoapAgent& ai) const override;
	virtual void reset() override;
private:
	float reloadTime;
	float currentReloadTime;
};
