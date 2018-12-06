#pragma once

#include <utility>
#include "Attack.h"

struct Character
{
public:
	float hit_box;
	std::string id;
	const char *file_path;
	std::vector<Attack> attacks;
	float velocity;

	Character()
	{
		attacks.push_back(Attack(WHIP_RANGE, WHIP_DISTANCE, Whip));
		attacks.push_back(Attack(JUMP_KICK_RANGE, JUMP_KICK_DISTANCE, Jump_Kick));
		attacks.push_back(Attack(GRAB_RANGE, GRAB_DISTANCE, Grab));
		attacks.push_back(Attack(0, -2, Nothing));

		hit_box = 0.5f;
		id = "fighter";
		file_path = "fighter_full.png";
		velocity = 1.0;
	}

	Character(const float hit_box, const Attack whip, const Attack jump_kick, const Attack grab, const Attack nothing, std::string name, const float vel, const char * file)
		: hit_box(hit_box), id(std::move(name)), velocity(vel), file_path(file)
	{
		attacks.push_back(whip);
		attacks.push_back(jump_kick);
		attacks.push_back(grab);
		attacks.push_back(nothing);
	}

	~Character()
	{}
};
