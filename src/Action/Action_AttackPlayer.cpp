#include "Action_AttackPlayer.h"

Action_AttackPlayer::Action_AttackPlayer():
	GoapAction(1, "AttackPlayer")
{
	addPrecondition("has_weapon", true);
	addPrecondition("has_ammo", true);
	addPrecondition("is_in_range", true);
}
