#include "GetFood.h"
#include <iostream>

void GetFood::Execute(Village& village) const
{
	village.AddFood(5);
	std::cout << "Get Food : " << village.GetFoodReserve() << std::endl;
}

float GetFood::Evaluation(Village& village) const
{
	float utilityFood = (MAX_FOOD_SIZE - static_cast<float>(village.GetFoodReserve())) / MAX_FOOD_SIZE;
	std::cout << "Evaluation Food : " << utilityFood << std::endl;
	return utilityFood;
}