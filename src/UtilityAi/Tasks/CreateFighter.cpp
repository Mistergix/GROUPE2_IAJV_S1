#include "CreateFighter.h"
#include "../Inhabitants/Fighter.h"
#include <iostream>
#include <math.h>
void CreateFighter::Execute(Village& village) const
{
	village.sizeFighters++;
	village.UseFood(6);
	std::cout << "Create fighter : " << village.sizeFighters << std::endl;
}

float CreateFighter::Evaluation(Village& village) const
{
	float utilityFood = 1-((MAX_FOOD_SIZE - static_cast<float>(village.GetFoodReserve())) / MAX_FOOD_SIZE);
	float utilityFighter = (MAX_FIGHTER_SIZE - village.sizeFighters) / static_cast<float>(MAX_FIGHTER_SIZE);
	auto s = (utilityFood + utilityFighter) / 2;
	std::cout << "Evaluation create fighter : " << s << std::endl;

	return s;
}
