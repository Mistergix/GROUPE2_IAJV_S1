#include <iostream>

#include "EnemyAI.h"
#include "World.h"

int main()
{
	EnemyAI enemyAI;
	World world(3);

	enemyAI.AddState("HasAmmo", false);
	enemyAI.AddState("HasWeapon", true);
	enemyAI.AddState("PlayerInRange", false);

	std::unordered_map<std::string, bool> goalState;

	goalState["DecreasePlayerLife"] = true;

	while (world.playerLife > 0) {
		while (!enemyAI.HasPlan()) {
			enemyAI.PlanSequenceOfAction(goalState);
		}

		while (enemyAI.HasPlan()) {
			enemyAI.PerformAction(world);
		}
	}
}
