#include "CombatProcesses.h"
#include "stdafx.h"

bool CleanUp::do_work()
{
	if (p1_pc_->num_wins >= ROUNDWIN || p2_pc_->num_wins >= ROUNDWIN)
		processor_->match_winner();
	else
	{
		p1_pc_->change_priority();
		p2_pc_->change_priority();

		p1_pc_->choose_attack(Nothing);
		p2_pc_->choose_attack(Nothing);

		p1_pc_->attack_used = false;
		p2_pc_->attack_used = false;

		processor_->create_combat();
	}
	work_complete_ = 1;
	return true;
}

Entity* EndOfRoundSequence::check_winner(Entity* entity)
{
	Entity * winner = nullptr;

	if (Collision::aabb(SDL_Rect{priority_collider_->projectile_point, priority_collider_->collider.y, static_cast<int>(priority_player_->chosen_attack->projectile_range * priority_transform_->scale * priority_transform_->height) * priority_player_->direction, static_cast<int>(priority_transform_->scale * priority_transform_->height) }, other_collider_->collider) ||
		Collision::aabb(SDL_Rect{other_collider_->projectile_point, other_collider_->collider.y, static_cast<int>(other_player_->chosen_attack->projectile_range * other_transform_->scale * other_transform_->height) * other_player_->direction, static_cast<int>(other_transform_->scale * other_transform_->height) }, priority_collider_->collider)
		)
	{
		entity->get_component<TransformComponent>().net_velocity.x = 0;
		entity->get_component<TransformComponent>().external_velocity.x = 0;
		entity->get_component<TransformComponent>().player_velocity.x = 0;
		entity->get_component<SpriteComponent>().animated = true;

		// tiny jump kick exception
		if (priority_player_->chosen_attack->attack_id == Jump_Kick && other_player_->chosen_attack->attack_id == Whip)
		{
			auto current_distance = std::abs(priority_transform_->position.x - other_transform_->position.x) / (priority_transform_->scale * priority_transform_->height);

			if (priority_player_->chosen_attack->projectile_range * priority_transform_->scale * priority_transform_->height >= current_distance)
				winner = priority_;
		}
		else
		{
			winner = priority_player_->check_attack_winner(other_);
		}
	}

	return winner;
}

bool EndOfRoundSequence::move_player(Entity * entity, int distance)
{
	auto current_distance = std::abs(priority_transform_->position.x - other_transform_->position.x);
	auto transform = &entity->get_component<TransformComponent>();
	auto player = &entity->get_component<PlayerComponent>();
	auto sprite = &entity->get_component<SpriteComponent>();

	if (starting_distance_unset_)
	{
		starting_distance_ = current_distance;
		starting_distance_unset_ = false;
	}
	
	if (starting_distance_ + abs(distance) <= current_distance
		|| starting_distance_ - abs(distance) >= current_distance)
	{
		transform->net_velocity.x = 0;
		transform->external_velocity.x = 0;
		transform->player_velocity.x = 0;
		sprite->animated = true;
		player->attack_used = true;
		starting_distance_ = current_distance;
		return true;
	}
	else
	{
		sprite->animated = false;
		auto move_direction = player->chosen_attack->move_distance / std::abs(player->chosen_attack->move_distance);

		transform->player_velocity.x = player->get_velocity() * player->direction * move_direction;

		if (transform->scale == SPRITE_SCALING)
			transform->net_velocity.x = transform->player_velocity.x + transform->external_velocity.x;
	}

	return false;
}

bool EndOfRoundSequence::do_work()
{
	auto current_distance = std::abs(priority_transform_->position.x - other_transform_->position.x) / (priority_transform_->scale * priority_transform_->height);

	if (attack_unset_)
	{
		priority_attack_ = priority_player_->chosen_attack;
		other_attack_ = other_player_->chosen_attack;
		attack_unset_ = false;
		priority_movement_ = priority_attack_->move_distance * priority_transform_->scale * priority_transform_->height * priority_player_->direction * priority_player_->player_identity.hit_box;
		other_movement_ = other_attack_->move_distance * other_transform_->scale * other_transform_->height * other_player_->direction * other_player_->player_identity.hit_box;
	}

	Entity* winner = nullptr;

	if (priority_player_->chosen_attack->attack_id == Nothing && !priority_player_->attack_used)
	{
		if (!move_player(priority_, priority_movement_) || PLAYER_MAX_RANGE >= current_distance + FLT_EPSILON)
			return false;
	}
	if (other_player_->chosen_attack->attack_id == Nothing && !other_player_->attack_used)
	{
		if (!move_player(other_, other_movement_) || PLAYER_MAX_RANGE >= current_distance + FLT_EPSILON)
			return false;
	}
	
	if (!priority_player_->attack_used)
	{
		
		if ((winner = check_winner(priority_)) )
		{
			winner->get_component<PlayerComponent>().round_win();
			processor_->end_of_round(winner);
			return true;
		}
		if (!move_player(priority_, priority_movement_))
			return false;
	}

	if (!other_player_->attack_used)
	{
		if ((winner = check_winner(other_)))
		{
			winner->get_component<PlayerComponent>().round_win();
			processor_->end_of_round(winner);
			return true;
		}
		if (!move_player(other_, other_movement_))
			return false;
	}
}
