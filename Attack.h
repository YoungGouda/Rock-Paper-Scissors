#pragma once
#include "Animation.h"
#include <string>


struct Attack
{

	float Range;
	float whifDistance;
	std::string animID;

	Attack(float rng, float wDist, std::string ID)
	{
		Range = rng;
		whifDistance = wDist;
		animID = ID;
	}

	Attack()
	{
		Range = WHIP_RANGE;
		whifDistance = WHIP_WHIF;
		animID = "whip";
	}
};