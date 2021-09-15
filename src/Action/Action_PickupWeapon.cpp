#include "Action_PickupWeapon.h"

Action_PickupWeapon::Action_PickupWeapon():
	GoapAction(3, "PickupWeapon")
{
	addEffect("is_in_range", false);
	addEffect("has_weapon", true);
	addEffect("has_ammo", true);
}
