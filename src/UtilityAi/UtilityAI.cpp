#include "Inhabitants/Villager.h"
#include "Inhabitants/Fighter.h"
#include "Tasks/CreateVillager.h"
#include "Tasks/CreateFighter.h"
#include "Tasks/GetFood.h"
#include "Tasks/GetWood.h"
#include "Tasks/BuildHouse.h"
#include "UtilityAI.h"

#include "windows.h"
#include <iostream>

void UtilityAI::ExecuteUtilityAI()
{
	Village village = Village();
	Villager villager = Villager(village);
	Fighter fighter = Fighter(village);

	CreateVillager* createVillagerTask = new CreateVillager();
	CreateFighter* createFighterTask = new CreateFighter();
	GetFood* getFood = new GetFood();
	GetWood* getWood = new GetWood();
	BuildHouse* buildHouse = new BuildHouse();

	village.AddTask(createVillagerTask);
	village.AddTask(createFighterTask);
	village.AddTask(getFood);
	village.AddTask(getWood);
	village.AddTask(buildHouse);

	int nbIt = 0;
	while (nbIt < 50) {
		village.ExecuteBestTask();
		nbIt++;
	}
	std::cout << village.sizeVillagers << " Villagers created" << std::endl;
	std::cout << village.sizeFighters << " Fighters created" << std::endl;
	std::cout << village.GetFoodReserve() << " Food remaining" << std::endl;
	std::cout << village.GetWoodReserve() << " Wood remaining" << std::endl;
	std::cout << village.numberHouses << " Houses created" << std::endl;
}