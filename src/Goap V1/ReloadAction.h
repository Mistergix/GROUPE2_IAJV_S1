#pragma once

#include "GoapActionV1.h"

class ReloadAction : public GoapActionV1 {
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