#pragma once

#include "GoapAction.h"

class MoveToPlayerAction : public GoapAction {
public:
	MoveToPlayerAction(float cost, std::string name);
	virtual bool TryPerformAction(World& world, GoapAI& ai) override;
	virtual bool Finished() const override;
	virtual bool CanDoActionInContext(World& world, GoapAI& ai) const override;
	virtual void Reset() override;
private :
	float timeToMove;
	float currentTimeToMove;
};