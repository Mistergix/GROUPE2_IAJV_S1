#pragma once

#include "GoapActionV1.h"

class GetWeaponAction : public GoapActionV1 {
public:
	GetWeaponAction(float cost, std::string name);
	virtual bool TryPerformAction(World& world, GoapAI& ai) override;
	virtual bool Finished() const override;
	virtual bool CanDoActionInContext(World& world, GoapAI& ai) const override;
	virtual void Reset() override;
private :
	float timeToGetWeapon;
	float currentTimeToGetWeapon;
};