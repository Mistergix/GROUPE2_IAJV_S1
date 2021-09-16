#pragma once

#include "GoapActionV1.h"

class AttackPlayerAction : public GoapActionV1 {
public:
	AttackPlayerAction(float cost, std::string name);
	virtual bool TryPerformAction(World& world, GoapAI& ai) override;
	virtual bool Finished() const override;
	virtual bool CanDoActionInContext(World& world, GoapAI& ai) const override;
	virtual void Reset() override;
};