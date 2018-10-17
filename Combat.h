#pragma once
#include "GameState.h"

extern Manager manager;

class Combat : public GameState
{
public:
	Combat(Entity* p_left, Entity * p_right, Entity * bg);

	~Combat();
	void handle_events() override;
	void logic() override;
	void render() override;


	Entity * player_left, * player_right, * background;
};
