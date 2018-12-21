#pragma once
#include "ECS.h"
#include "Constants.h"
#include "SpriteComponent.h"
#include "PlayerComponent.h"
#include "Command.h"


class CombatProcessor;

class EndRoundCommand : public Command
{
	CombatProcessor * processor_;
public:
	EndRoundCommand(CombatProcessor * processor)
		: processor_(processor)
	{}
	~EndRoundCommand()
	{}

	void execute(Entity * entity) override;
};


class MoveCommand : public Command
{
public:
	MoveCommand( const float v_scale, const ANIMATIONS anim_id) :
		x_before_(0), velocity_scale_(v_scale), anim_id_(anim_id)
	{}

	~MoveCommand()
	{}


	void execute(Entity * entity) override
	{
		auto transform = &entity->get_component<TransformComponent>();
		transform->player_velocity.x = velocity_scale_ * entity->get_component<PlayerComponent>().get_velocity();
		transform->net_velocity.x = 0.0f;
		entity->get_component<SpriteComponent>().play(anim_id_);
		
		if (transform->scale == SPRITE_SCALING)
			transform->net_velocity.x = transform->player_velocity.x + transform->external_velocity.x;
	}

	void idle(Entity* entity) override
	{}


private:
	float x_before_;
	float velocity_scale_;
	ANIMATIONS anim_id_;
};


class SelectAttackCommand : public Command
{
public:
	SelectAttackCommand(const ATTACKS att_id )
		: was_pressed_(false), attack_id_(att_id)
	{}

	~SelectAttackCommand()
	{}

	void execute(Entity * entity) override
	{
		was_pressed_ = true;
	}
	void idle(Entity* entity) override
	{
		if (was_pressed_)
		{
			entity->get_component<PlayerComponent>().choose_attack(attack_id_);
			was_pressed_ = false;
		}
	}

private:
	std::vector<std::string> attacks = {"whip", "jump kick", "grab"};
	bool was_pressed_;
	ATTACKS attack_id_;
};

class PauseGameCommand : public Command
{
public:
	PauseGameCommand()
	{}

	void execute(Entity * entity) override
	{
	}
	void idle(Entity* entity) override
	{}


private:
};


class MoveCursorXCommand : public Command
{
public:
	MoveCursorXCommand(const int x)
		: was_pressed_(false), x_increment_(x), count_(0), frequency_(CURSOR_FREQUENCY)
	{}

	void execute(Entity * entity) override
	{
		was_pressed_ = true;

		if (count_% frequency_ == 0)
		{
			const auto options = &entity->get_component<OptionsComponent>();
			options->next_x(x_increment_);
			frequency_ = std::max(frequency_ - 1, 1);
		}
		count_++;
	}

	void idle(Entity* entity) override
	{
		if (was_pressed_)
		{
			const auto options = &entity->get_component<OptionsComponent>();
			options->next_x(x_increment_);
			count_ = 0;
			frequency_ = CURSOR_FREQUENCY;
			was_pressed_ = false;
		}
	}


private:
	bool was_pressed_;
	int x_increment_, count_, frequency_;
};

class MoveCursorYCommand : public Command
{
public:
	MoveCursorYCommand( const int y)
		: was_pressed_(false), y_increment_(y), count_(0), frequency_(CURSOR_FREQUENCY)
	{}

	void execute(Entity * entity) override
	{
		if (count_% frequency_ == 0)
		{
			const auto options = &entity->get_component<OptionsComponent>();
			options->next_y(y_increment_);
			frequency_ = std::max(frequency_ - 3, 3);
		}
		was_pressed_ = true;
		count_++;
	}

	void idle(Entity* entity) override
	{
		if (was_pressed_)
		{
			count_ = 0;
			frequency_ = CURSOR_FREQUENCY;
			was_pressed_ = false;
		}
	}

private:
	bool was_pressed_;
	int y_increment_, count_, frequency_;
};

class MakeSelection : public Command
{
public:
	MakeSelection()
		:was_pressed_(false)
	{}

	void execute(Entity* entity) override
	{
		was_pressed_ = true;
	}

	void idle(Entity* entity) override
	{
		if (was_pressed_)
		{
			auto options = &entity->get_component<OptionsComponent>();
			options->get_current_link()->get_command()->execute(entity);
			was_pressed_ = false;
		}
	}

private:
	bool was_pressed_;

};


class GoToMenuCommand : public Command
{
public:
	GoToMenuCommand()
		:was_pressed_(false)
	{}

	void execute(Entity* entity) override
	{
		was_pressed_ = true;
	}
	void idle(Entity* entity) override
	{
		if (was_pressed_)
		{
			if (Game::state_id != STATE_MENU)
				Game::set_next_state(STATE_MENU);
			was_pressed_ = false;
		}

	}
private:
	bool was_pressed_;

};

