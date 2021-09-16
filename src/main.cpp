#include <iostream>

#include "Goap V1/EnemyAI.h"
#include "Goap V1/World.h"
#include "Goap V1/AttackPlayerAction.h"
#include "Goap V1/GetWeaponAction.h"
#include "Goap V1/MoveToPlayerAction.h"
#include "Goap V1/ReloadAction.h"
#include "Goap V1/IdleAction.h"

#include "GoapAgent.h"

int main()
{
	GoapAgent agent;
	agent.makePlan();

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
			enemyAI.PlanSequenceOfAction(goalState, world);
		}

		while (enemyAI.HasPlan()) {
			enemyAI.PerformAction(world);
		}
	}
}
