#include <iostream>

#include "Goap V1/EnemyAI.h"
#include "Goap V1/World.h"
#include "Goap V1/AttackPlayerAction.h"
#include "Goap V1/GetWeaponAction.h"
#include "Goap V1/MoveToPlayerAction.h"
#include "Goap V1/ReloadAction.h"
#include "Goap V1/IdleAction.h"

#include "GoapAgent.h"
#include "Action/Action_AttackPlayer.h"
#include "Action/Action_MoveToPlayer.h"
#include "Action/Action_PickupWeapon.h"
#include "Action/Action_Reload.h"
#include "Action/Action_Idle.h"

int main()
{
	World world(3);

	GoapAgent agent("Enemy 1", std::make_unique<Action_AttackPlayer>(), std::make_unique<Action_Idle>());

	agent.addState("has_ammo", false);
	agent.addState("has_weapon", true);
	agent.addState("is_in_range", false);

	agent.addAction(std::make_unique<Action_MoveToPlayer>());
	agent.addAction(std::make_unique<Action_PickupWeapon>());
	agent.addAction(std::make_unique<Action_Reload>());

	// TODO
	// Update World, and enemies states

	while (world.playerLife > 0) {
		agent.makePlan();
		while (agent.hasPlan()) {
			agent.performAction(world);
		}
	}
}
