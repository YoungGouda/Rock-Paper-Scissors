#pragma once
#include "Process.h"
#include <string>
#include "Game.h"
#include "Background.h"
#include "Collision.h"
#include "EndOfRound.h"

class CombatProcessor;

class ResetGame : public Process
{
	float work_complete_;
	TransformComponent * left_transform_, *right_transform_, *background_transform_;
public:
	ResetGame(Entity* player_left, Entity * player_right, Entity * background)
		: work_complete_(0)
	{
		left_transform_ = &player_left->get_component<TransformComponent>();
		right_transform_ = &player_right->get_component<TransformComponent>();
		background_transform_ = &background->get_component<TransformComponent>();
	}

	bool do_work() override
	{
		left_transform_->scale = SPRITE_SCALING;
		right_transform_->scale = SPRITE_SCALING;
		background_transform_->scale = BACKGROUND_SCALING;

		left_transform_->position = Vector2D(SPRITE_LEFT_EDGE_OF_SCREEN, SPRITE_BOTTOM_OF_SCREEN);
		right_transform_->position = Vector2D(SPRITE_RIGHT_EDGE_OF_SCREEN, SPRITE_BOTTOM_OF_SCREEN);
		background_transform_->position = Vector2D(BACKGROUND_X_OFFSET, BACKGROUND_Y_OFFSET);	

		work_complete_ = 1;
		return true;
	}

	float work_done() override { return work_complete_; }
};

class DrawAttackLines : public Process
{
	ColliderComponent * left_collider_,* right_collider_;
	Timer * delay_time;
	int total_delay_;
public:
	DrawAttackLines(Entity * player_left, Entity * player_right, int delay)
		: total_delay_(delay)
	{
		left_collider_ = &player_left->get_component<ColliderComponent>();
		right_collider_ = &player_right->get_component<ColliderComponent>();
		
		delay_time = new Timer();
	}
	~DrawAttackLines() {}

	bool do_work() override
	{
		if (!delay_time->is_started())
		{
			delay_time->start();
			left_collider_->draw_attack = true;
			right_collider_->draw_attack = true;

			left_collider_->set_color(255, 0, 0);
			right_collider_->set_color(0, 0, 255);
		}


		if (delay_time->get_ticks() >= total_delay_)
		{

			left_collider_->draw_attack = false;
			right_collider_->draw_attack = false;
			return true;
		}
		return false;
	}

	float work_done() override
	{
		return delay_time->get_ticks() / total_delay_;
	}

};

class EndOfRoundSequence : public Process
{
	Entity* priority_, *other_;
	CombatProcessor * processor_;
	PlayerComponent * priority_player_, *other_player_;
	Attack * priority_attack_, * other_attack_;
	TransformComponent * priority_transform_, *other_transform_;
	bool starting_distance_unset_, attack_unset_;
	float starting_distance_;
	ColliderComponent * priority_collider_, * other_collider_;

	float other_movement_, priority_movement_, other_range_, priority_range_;

public:
	EndOfRoundSequence(Entity *player1, Entity* player2, CombatProcessor* processor)
		: processor_(processor), starting_distance_unset_(true), attack_unset_(true)
	{
		priority_ = player1;
		other_ = player2;

		if (player2->get_component<PlayerComponent>().is_priority_player)
		{
			priority_ = player2;
			other_ = player1;
		}

		priority_player_ = &priority_->get_component<PlayerComponent>();
		other_player_ = &other_->get_component<PlayerComponent>();

		priority_transform_ = &priority_->get_component<TransformComponent>();
		other_transform_ = &other_->get_component<TransformComponent>();

		priority_collider_ = &priority_->get_component<ColliderComponent>();
		other_collider_ = &other_->get_component<ColliderComponent>();
	}

	Entity * check_winner(Entity * entity);

	bool move_player(Entity * entity, int distance);

	bool do_work() override;

	float work_done() override { return 0; }
};

class CombatCollision : public Process
{
	Entity * player_left_, * player_right_;
public:
	CombatCollision(Entity * player_left, Entity * player_right)
		: player_left_(player_left), player_right_(player_right)
	{}

	bool do_work() override
	{
		if (Collision::aabb(player_left_->get_component<ColliderComponent>().collider,
			player_right_->get_component<ColliderComponent>().collider))
		{
			player_right_->get_component<TransformComponent>().position.x -= player_right_->get_component<TransformComponent>().player_velocity.x * PLAYER_SPEED - 1;
			player_left_->get_component<TransformComponent>().position.x -= player_left_->get_component<TransformComponent>().player_velocity.x * PLAYER_SPEED + 1;
		}
		return true;
	}

	float work_done() override{ return 1; }
};

class StopRound : public Process
{
	float work_complete_;
	Entity * player_left_, *player_right_;
public:
	StopRound(Entity * player_left, Entity * player_right)
		: player_left_(player_left), player_right_(player_right), work_complete_(0)
	{}
	bool do_work() override
	{
		player_left_->get_component<TransformComponent>().net_velocity.x = 0;
		player_right_->get_component<TransformComponent>().net_velocity.x = 0;
		player_left_->get_component<TransformComponent>().player_velocity.x = 0;
		player_right_->get_component<TransformComponent>().player_velocity.x = 0;

		player_left_->get_component<SpriteComponent>().play(Idle);
		player_right_->get_component<SpriteComponent>().play(Idle);

		player_left_->get_component<ControllerComponent>().change_controller("nothing");
		player_right_->get_component<ControllerComponent>().change_controller("nothing");
		work_complete_ = 1;
		return true;
	}

	float work_done() override { return work_complete_; }
};

class CalculateAttackOutcome : public Process
{
	float work_complete_;
	EndOfRound * end_of_round_;
public:
	CalculateAttackOutcome(Entity * player_left, Entity * player_right)
	{
		auto priority_ = player_left;
		auto other_ = player_right;
		if (player_right->get_component<PlayerComponent>().is_priority_player)
		{
			priority_ = player_right;
			other_ = player_left;
		}

		end_of_round_ = new EndOfRound(priority_, other_);
	}

	bool do_work() override 
	{

		return false;
	}
	float work_done() override { return work_complete_; }

	
};

class ProjectileMovement : public Process
{
	Vector2D velocity_, distance_;
	TransformComponent * asset_tc_;
	Timer * timer_;
	ProjectileMovement(Entity * asset, Vector2D distance, Vector2D velocity)
		: distance_(distance), velocity_(velocity)
	{
		asset_tc_ = &asset->get_component<TransformComponent>();
		timer_ = new Timer();
	}

	bool do_work()
	{
		if (!timer_->is_started())
		{
			timer_->start();
		}
		asset_tc_->position += Vector2D(velocity_.x * timer_->get_ticks(), velocity_.y * timer_->get_ticks() - 4.9 * std::pow(timer_->get_ticks(), static_cast<Uint32>(2)));
		if (asset_tc_->position >= distance_)
		{
			timer_->stop();
			return true;
		}
		return false;
	}

	float work_done()
	{
		auto work_complete = asset_tc_->position / distance_;
		return (work_complete.x + work_complete.y) / 2;
	}

};

class PlayAnimation : public Process
{
	float work_complete_;
	SpriteComponent * asset_sc_;
	ANIMATIONS animation;
public:
	PlayAnimation(Entity * asset, ANIMATIONS animation)
		: work_complete_(0)
	{
		asset_sc_ = &asset->get_component<SpriteComponent>();
	}

	bool do_work()
	{
		asset_sc_->play(animation);
		work_complete_ = 1;
		return true;
	}

	float work_done() { return work_complete_; }
};

class CleanUp : public Process
{
	float work_complete_;
	PlayerComponent * p1_pc_, *p2_pc_;
	CombatProcessor *processor_;
public:
	CleanUp(Entity * player_left, Entity * player_right, CombatProcessor * processor)
		: work_complete_(0), processor_(processor)
	{
		p1_pc_ = &player_left->get_component<PlayerComponent>();
		p2_pc_ = &player_right->get_component<PlayerComponent>();
	}

	bool do_work();

	float work_done() { return work_complete_; }
};