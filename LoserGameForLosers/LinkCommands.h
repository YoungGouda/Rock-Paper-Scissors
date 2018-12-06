#pragma once
#include "Command.h"
#include "Game.h"
#include "GameState.h"

class ChangeStateCommand : public Command
{
	game_states state_;
public:
	explicit ChangeStateCommand(game_states new_state)
		: state_(new_state)
	{}

	void execute(Entity* entity) override
	{
		if (Game::state_id != state_)
			Game::set_next_state(state_);
	}

	void idle(Entity* entity) override{}

};

class ChangeScreenCommand : public Command
{
public:
	ChangeScreenCommand() {}

	void execute(Entity * entity) override
	{}

	void idle(Entity * entity) override
	{}

};

class NothingCommand : public Command
{
public:
	NothingCommand()
	{}

	void execute(Entity* entity) override
	{}

	void idle(Entity* entity) override{}

};