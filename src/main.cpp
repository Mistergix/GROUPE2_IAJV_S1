#include <iostream>

#include "EnemyAI.h"
#include "World.h"
#include "AttackPlayerAction.h"
#include "GetWeaponAction.h"
#include "MoveToPlayerAction.h"
#include "ReloadAction.h"
#include "IdleAction.h"

int main()
{
	World world(3);

	EnemyAI enemyAI1;

	enemyAI1.AddState("HasAmmo", true);
	enemyAI1.AddState("HasWeapon", true);
	enemyAI1.AddState("PlayerInRange", true);


	EnemyAI enemyAI;
	

	enemyAI.AddState("HasAmmo", false);
	enemyAI.AddState("HasWeapon", true);
	enemyAI.AddState("PlayerInRange", false);

	IdleAction idle(1.0f);

	AttackPlayerAction attackPlayer(1.0f);

	GetWeaponAction getWeapon(3.0f);

	ReloadAction reload(1.0f);
	reload.reloadTime = 1.0f;

	MoveToPlayerAction moveToPlayer(3.0f);

	enemyAI.AddAction(attackPlayer);
	enemyAI.AddAction(getWeapon);
	enemyAI.AddAction(reload);
	enemyAI.AddAction(moveToPlayer);

	enemyAI.SetDefaultAction(&idle);

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
