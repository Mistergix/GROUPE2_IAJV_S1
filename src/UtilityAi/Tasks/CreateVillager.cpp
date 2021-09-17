#include "CreateVillager.h"
#include "../Inhabitants/Villager.h"
#include <iostream>
#include <math.h>

void CreateVillager::Execute(Village& village) const
{
	village.sizeVillagers++;
	village.UseFood(5);
	std::cout << "Create villager : " << village.sizeVillagers << std::endl;
}

float CreateVillager::Evaluation(Village& village) const
{
	float utilityFood = 1-((MAX_FOOD_SIZE - static_cast<float>(village.GetFoodReserve())) / MAX_FOOD_SIZE);
	float utilityVillager = (MAX_VILLAGER_SIZE-village.sizeVillagers) / static_cast<float>(MAX_VILLAGER_SIZE);

	auto s = (utilityFood + utilityVillager) / 2;
	std::cout << "Evaluation create villager : " << s << std::endl;
	return s;
}

