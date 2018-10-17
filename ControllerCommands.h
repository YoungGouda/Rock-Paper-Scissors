#pragma once
#include "ECS.h"
#include "Constants.h"
#include "SpriteComponent.h"
#include "PlayerComponent.h"
#include "CursorComponent.h"
#include "Command.h"


class MoveCommand : public Command
{
public:
	MoveCommand( const float v_scale, const char* anim_id) :
		x_before_(0), velocity_scale_(v_scale), anim_id_(anim_id)
	{
	}

	~MoveCommand()
	{
	}


	void execute(Entity * entity) override
	{
		x_before_ = entity->get_component<TransformComponent>().position.x;

		entity->get_component<SpriteComponent>().play(anim_id_);
		if (entity->get_component<TransformComponent>().scale >= SPRITE_SCALING)
			entity->get_component<TransformComponent>().velocity.x = entity->get_component<PlayerComponent>().get_velocity() * velocity_scale_;
	}

	void undo(Entity * entity) override
	{
		entity->get_component<TransformComponent>().position.x = x_before_;
	}

private:
	float x_before_;
	float velocity_scale_;
	const char * anim_id_;
};


class SelectAttackCommand : public Command
{
public:
	SelectAttackCommand( const char * att_id ) : attack_id_(att_id)
	{}

	~SelectAttackCommand()
	{}

	void execute(Entity * entity) override
	{
		previous_att_id_ = entity->get_component<PlayerComponent>().chosen_attack.attack_id;
		entity->get_component<PlayerComponent>().choose_attack(attack_id_);
		std::cout << entity->get_component<PlayerComponent>().player_name << ": chooses " << entity->get_component<PlayerComponent>().chosen_attack.attack_id << std::endl;
	}

	void undo(Entity * entity) override
	{
		entity->get_component<PlayerComponent>().choose_attack(previous_att_id_);
	}
private:
	const char* previous_att_id_;
	const char * attack_id_;
};

class PauseGameCommand : public Command
{
public:
	PauseGameCommand()
	{}

	void execute(Entity * entity) override
	{
	}

	void undo(Entity * entity) override
	{
	}
private:
};


class MoveCursorXCommand : public Command
{
public:
	MoveCursorXCommand(const int x)
		: x_increment_(x)
	{}
	void execute(Entity * entity) override
	{
		const auto options = &entity->get_component<OptionsComponent>();

		options->next_x( x_increment_);
	}

	void undo(Entity * entity) override
	{
		const auto options = &entity->get_component<OptionsComponent>();

		options->next_x(-x_increment_);
	}

private:
	int x_increment_;
};

class MoveCursorYCommand : public Command
{
public:
	MoveCursorYCommand( const int y)
		:  y_increment_(y)
	{}
	void execute(Entity * entity) override
	{
		const auto options = &entity->get_component<OptionsComponent>();

		options->next_y(y_increment_);
	}

	void undo(Entity * entity) override
	{
		const auto options = &entity->get_component<OptionsComponent>();

		options->next_y(-y_increment_);
	}

private:
	int y_increment_;
};

class MakeSelection : public Command
{
public:
	MakeSelection()
	{}

	void execute(Entity* entity) override
	{
		auto options = &entity->get_component<OptionsComponent>();
		options->get_current_link()->get_command()->execute(entity);
	}

	void undo(Entity* entity) override
	{
		
	}

};


class GoToMenuCommand : public Command
{
public:
	GoToMenuCommand()
	{}

	void execute(Entity* entity) override
	{
		if (Game::state_id != STATE_MENU)
			Game::set_next_state(STATE_MENU);
	}

	void undo(Entity* entity) override
	{

	}

};