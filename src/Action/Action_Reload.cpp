#include "Action_Reload.h"

Action_Reload::Action_Reload():
	GoapAction(1, "Reload")
{
	addPrecondition("has_weapon", true);
	addEffect("has_ammo", true);
}
