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

	EnemyAI enemyAI("Enemy 1");
	
	enemyAI.AddState("HasAmmo", false);
	enemyAI.AddState("HasWeapon", true);
	enemyAI.AddState("PlayerInRange", false);

	IdleAction idle(1.0f, "IDLE");

	AttackPlayerAction attackPlayer(1.0f, "ATTACK");

	GetWeaponAction getWeapon(3.0f, "GET WEAPON");

	ReloadAction reload(1.0f, "RELOAD");
	reload.reloadTime = 1.0f;

	MoveToPlayerAction moveToPlayer(3.0f, "MOVE");

	enemyAI.AddAction(attackPlayer);
	enemyAI.AddAction(getWeapon);
	enemyAI.AddAction(reload);
	enemyAI.AddAction(moveToPlayer);

	enemyAI.SetDefaultAction(&idle);

	std::unordered_map<std::string, bool> goalState;

	goalState["DecreasePlayerLife"] = true;



	// TODO
	// Update World, and enemies states
	while (world.playerLife > 0) {
		while (!enemyAI.HasPlan()) {
			enemyAI.PlanSequenceOfAction(goalState);
		}

		while (enemyAI.HasPlan()) {
			enemyAI.PerformAction(world);
		}
	}
}
