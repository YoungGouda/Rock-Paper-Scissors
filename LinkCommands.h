#pragma once
#include "Command.h"
#include "Game.h"
#include "GameState.h"

class FreePlayCommand : public Command
{
public:
	FreePlayCommand()
	{}

	void execute(Entity* entity) override
	{
		if (Game::state_id != STATE_COMBAT)
			Game::set_next_state(STATE_COMBAT);
	}

	void undo(Entity* entity) override
	{}

};

class NothingCommand : public Command
{
public:
	NothingCommand()
	{}

	void execute(Entity* entity) override
	{}

	void undo(Entity* entity) override
	{}
};