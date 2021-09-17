#include "BuildHouse.h"
#include <iostream>

void BuildHouse::Execute(Village& village) const
{
	village.BuildHouse();
	village.UseWood(15);
	std::cout << "Build House" << std::endl;
}

float BuildHouse::Evaluation(Village& village) const
{
	if (village.GetWoodReserve() < 15) {
		return 0.0f;
	}
	float utilityBuild = ((NUMBER_HOUSE - static_cast<float>(village.numberHouses)) / NUMBER_HOUSE);
	float utilityWood = 1-((MAX_WOOD_SIZE - village.GetWoodReserve()) / MAX_WOOD_SIZE);
	float utilityVillager = 1-((MAX_VILLAGER_SIZE - village.sizeVillagers) / static_cast<float>(MAX_VILLAGER_SIZE));

	std::cout << "Evaluation build house : " << (utilityBuild + utilityWood + utilityVillager)/3 << std::endl;
	return (utilityBuild + utilityWood + utilityVillager) / 3;
}
