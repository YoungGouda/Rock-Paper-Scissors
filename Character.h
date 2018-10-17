#pragma once

#include <utility>
#include "Attack.h"

struct Character
{
public:
	float hit_box;
	std::string id;
	std::map<std::string, Attack> attacks;
	float velocity;

	Character()
	{
		attacks.emplace("jump kick", Attack(JUMP_KICK_RANGE, JUMP_KICK_WHIFF, "jump kick"));
		attacks.emplace("whip", Attack(WHIP_RANGE, WHIP_WHIFF, "whip"));
		attacks.emplace("grab", Attack(GRAB_RANGE, GRAB_WHIFF, "grab"));
		hit_box = 0.5f;
		id = "Brunis";
		velocity = 1.0;
	}

	Character(const float hit_box, Attack whip, Attack jump_kick, Attack grab, std::string name, const float vel)
		: hit_box(hit_box), id(std::move(name)), velocity(vel)
	{
		attacks.emplace(jump_kick.attack_id, jump_kick);
		attacks.emplace(whip.attack_id, whip);
		attacks.emplace(grab.attack_id, grab);
	}

	~Character()
	{
		attacks.clear();
	}
};
