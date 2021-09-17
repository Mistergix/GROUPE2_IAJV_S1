#pragma once
#include "../Inhabitants/Inhabitant.h"
#include "../Village.h"

class Fighter : public Inhabitant {
public:
	Fighter(Village& village) { village.AddFighter(); }
private:
};