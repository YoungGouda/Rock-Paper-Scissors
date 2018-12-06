#pragma once
#include <string>


struct Attack
{

	float projectile_range;
	float move_distance;
	ATTACKS attack_id;

	Attack(const float range, const float distance, const ATTACKS id) : projectile_range(range), move_distance(distance), attack_id(id)
	{}

	Attack()
	{
		projectile_range = WHIP_RANGE;
		move_distance = WHIP_DISTANCE;
		attack_id = Whip;
	}
};