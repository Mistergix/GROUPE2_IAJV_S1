#pragma once
#include <unordered_map>
#define MAX_VILLAGER_SIZE 10
#define MAX_FIGHTER_SIZE 5
#define MAX_FOOD_SIZE 30
#define MAX_WOOD_SIZE 40
#define FOOD_COST 7.5f
#define NUMBER_HOUSE 2
#include "Task.h"
#include <list>
class Inhabitant;
class Village {
public:
	Village() : foodReserve(0), woodReserve(0), idleTime(.3f), attackProbability(.6f), sizeVillagers(0), sizeFighters(0), currentTask(NULL), numberHouses(0) {}
	float GetFoodReserve() const;
	float GetIdleTime() const;
	float GetAttackProbability() const;
	float GetWoodReserve() const;
	void SetIdleTime(float newIdleTime);
	void SetAttackProbability(float newProbability);
	
	void AddTask(Task* task);
	void AddVillager();
	void AddFighter();
	void ExecuteBestTask();
	void AddFood(int food);
	void UseFood(int cost);
	void UseWood(int cost);
	void AddWood(int wood);
	void BuildHouse();
	int sizeVillagers;
	int sizeFighters;
	int numberHouses;

private:
	std::list<Task*> possibleTasks;
	Task* currentTask;
	float foodReserve;
	float woodReserve;
	float idleTime;
	float attackProbability;
};