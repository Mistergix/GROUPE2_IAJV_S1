#pragma once
#include "../Inhabitants/Inhabitant.h"
#include "../Village.h"

class Villager : public Inhabitant{
public:
	Villager(Village& village) { village.AddVillager(); }
private:
};