#pragma once

#include "GoapAction.h"

class ReloadAction : public GoapAction {
public:
	ReloadAction(float cost, std::string name);
	virtual bool TryPerformAction(World& world, GoapAI& ai) override;
	virtual bool Finished() const override;
	virtual bool CanDoActionInContext(World& world, GoapAI& ai) const override;
	virtual void Reset() override;
	float reloadTime;
private :
	float currentReloadTime;
};