#include "GetWood.h"
#include <iostream>

void GetWood::Execute(Village& village) const
{
	village.AddWood(5);
	village.UseFood(4);
	std::cout << "Get Wood : " << village.GetWoodReserve() << std::endl;
}

float GetWood::Evaluation(Village& village) const
{
	float utilityWood = (MAX_WOOD_SIZE - village.GetWoodReserve()) / MAX_WOOD_SIZE;
	float utilityFood = 1-((MAX_FOOD_SIZE - static_cast<float>(village.GetFoodReserve())) / MAX_FOOD_SIZE);
	float utilityVillager = 1-((MAX_VILLAGER_SIZE - village.sizeVillagers) / static_cast<float>(MAX_VILLAGER_SIZE));
	float utilityFighter = 1-((MAX_FIGHTER_SIZE - village.sizeFighters) / static_cast<float>(MAX_FIGHTER_SIZE));

	std::cout << "Evaluation wood : " << (utilityFood + utilityWood + utilityVillager + utilityFighter) / 4 << std::endl;
	return (utilityFood + utilityWood + utilityVillager + utilityFighter) / 4;
}
