#pragma once
#include "GameState.h"
#include "CombatProcessor.h"

class Combat : public GameState
{
public:
	Combat(Manager * manager);
	~Combat();
	void handle_events() override;
	void logic() override;
	void render() override;
	void close() override;

private:
	Manager * manager_;
};
