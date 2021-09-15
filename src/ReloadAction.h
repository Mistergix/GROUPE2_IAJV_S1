#pragma once

#include "GoapAction.h"

class ReloadAction : public GoapAction {
public:
	ReloadAction(float cost);
	virtual void GeneratePreConditions();
	virtual void GenerateEffects();
	virtual bool TryPerformAction(World world);
	virtual bool Finished();
	virtual bool CanDoActionInContext(GoapAI& ai) const;
	virtual void Reset();
	float reloadTime;
private :
	float currentReloadTime;
};