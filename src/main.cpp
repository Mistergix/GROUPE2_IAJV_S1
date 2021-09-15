#include <iostream>

#include "EnemyAI.h"
#include "World.h"
#include "AttackPlayerAction.h"
#include "GetWeaponAction.h"
#include "MoveToPlayerAction.h"
#include "ReloadAction.h"

int main()
{
	EnemyAI enemyAI;
	World world(3);

	enemyAI.AddState("HasAmmo", false);
	enemyAI.AddState("HasWeapon", true);
	enemyAI.AddState("PlayerInRange", false);

	AttackPlayerAction attackPlayer;

	GetWeaponAction getWeapon;

	ReloadAction reload;
	reload.reloadTime = 1.0f;

	MoveToPlayerAction moveToPlayer;

	enemyAI.AddAction(attackPlayer);
	enemyAI.AddAction(getWeapon);
	enemyAI.AddAction(reload);
	enemyAI.AddAction(moveToPlayer);

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
