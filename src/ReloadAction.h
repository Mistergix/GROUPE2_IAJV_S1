#pragma once

#include "GoapAction.h"

class ReloadAction : public GoapAction {
	virtual void GeneratePreConditions();
	virtual void GenerateEffects();
	virtual bool TryPerformAction(World world);
	virtual bool Finished();
	virtual bool CanDoAction(GoapAI& ai) const;
	virtual void Reset();
};