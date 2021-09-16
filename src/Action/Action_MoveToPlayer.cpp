#include "Action_MoveToPlayer.h"

Action_MoveToPlayer::Action_MoveToPlayer():
	GoapAction(5, "MoveToPlayer")
{
	addEffect("is_in_range", true);
}
