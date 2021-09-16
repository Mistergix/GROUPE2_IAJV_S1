#pragma once

#include "GoapAction.h"

class ReloadAction : public GoapAction {
public:
	ReloadAction(float cost, float reloadTime);
	virtual bool TryPerformAction(World world);
	virtual bool Finished();
	virtual bool CanDoActionInContext(GoapAI& ai, World& world) const;
	virtual void Reset();
	float reloadTime;
private :
	float currentReloadTime;
};