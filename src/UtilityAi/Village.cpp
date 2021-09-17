#include <math.h>
#include <iostream>
#include "Village.h"
#include "Inhabitants/Villager.h"
#include "Tasks/GetFood.h"

void Village::AddTask(Task* task) {
	possibleTasks.push_back(task);
}

void Village::AddVillager()
{
	sizeVillagers++;
}

void Village::AddFighter()
{
	sizeFighters++;
}

void Village::AddFood(int food)
{
	if (foodReserve < MAX_FOOD_SIZE) {
		foodReserve += food;
		if (foodReserve > MAX_FOOD_SIZE)
		{
			foodReserve = MAX_FOOD_SIZE;
		}
	}
}

void Village::ExecuteBestTask()
{
	float bestTask = -1.0f;
	Task* currentTask = new GetFood();

	for (auto& task : possibleTasks) {
		float taskVal = task->Evaluation(*this);
		if (taskVal > bestTask) {
			bestTask = taskVal;
			currentTask = task;
		}
	}

	currentTask->Execute(*this);
	std::cout << std::endl;
}

float Village::GetFoodReserve() const
{
	return foodReserve;
}

float Village::GetIdleTime() const
{
	return idleTime;
}

float Village::GetAttackProbability() const
{
	return attackProbability;
}

float Village::GetWoodReserve() const
{
	return woodReserve;
}

void Village::SetIdleTime(float newIdleTime)
{
	idleTime = newIdleTime;
}

void Village::SetAttackProbability(float newProbability)
{
	attackProbability = newProbability;
}

void Village::UseFood(int cost)
{
	foodReserve -= cost;
}

void Village::UseWood(int cost)
{
	woodReserve -= cost;
}

void Village::AddWood(int wood)
{
	woodReserve += wood;
}

void Village::BuildHouse()
{
	numberHouses++;
}
