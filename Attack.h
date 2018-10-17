#pragma once
#include <string>


struct Attack
{

	float range;
	float whiff_distance;
	const char * attack_id;

	Attack(const float rng, const float w_dist, const char * id) : range(rng), whiff_distance(w_dist), attack_id(id)
	{}

	Attack()
	{
		range = WHIP_RANGE;
		whiff_distance = WHIP_WHIFF;
		attack_id = "whip";
	}
};