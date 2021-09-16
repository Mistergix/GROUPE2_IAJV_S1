#include <iostream>

#include "GoapAgent.h"
#include "Action/Action_AttackPlayer.h"
#include "Action/Action_AttackMelee.h"
#include "Action/Action_Teleport.h"
#include "Action/Action_MoveToPlayer.h"
#include "Action/Action_MoveToPlayerMelee.h"
#include "Action/Action_PickupWeapon.h"
#include "Action/Action_Reload.h"
#include "Action/Action_Idle.h"
#include "Action/Action_PutOnBoots.h"
#include "WorldV2.h"

int main()
{
	WorldV2 world(3, 1);

	//TODO Put Goal action in goap planner, currently we only put it in the constructor
	GoapAgent agent("Enemy 1", std::make_unique<Action_AttackMelee>(), std::make_unique<Action_Idle>());

	//TODO Refactor strings with in classes (to prevent the case sensitive problem)
	//TODO Replace bools with classes to evaluate at runtime 
	agent.addState("has_ammo", false);
	agent.addState("has_weapon", false);
	agent.addState("is_in_range_melee", false);
	agent.addState("is_in_range_distance", false);
	agent.addState("has_boots", true);
	agent.addState("has_teleporter", false);

	agent.addAction(std::make_unique<Action_MoveToPlayer>());
	agent.addAction(std::make_unique<Action_PickupWeapon>(1.5f));
	agent.addAction(std::make_unique<Action_Reload>());
	agent.addAction(std::make_unique<Action_MoveToPlayerMelee>());
	agent.addAction(std::make_unique<Action_Teleport>());
	agent.addAction(std::make_unique<Action_PutOnBoots>());

	// TODO
	// Update World, and enemies states

	while (world.playerLife > 0) {
		agent.makePlan();
		while (agent.hasPlan()) {
			agent.performAction(world);
		}
	}
}
