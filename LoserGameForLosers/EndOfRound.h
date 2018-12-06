#pragma once
#include "ECS.h"

class EndOfRound
{
	PlayerComponent * priority_pc_, * other_pc_;
	TransformComponent * priority_tc_, * other_tc_;
	ColliderComponent * priority_cc_, *other_cc_;
public:
	EndOfRound(Entity * player1, Entity * player2)
	{
		priority_pc_ = &player1->get_component<PlayerComponent>();
		other_pc_ = &player2->get_component<PlayerComponent>();

		priority_tc_ = &player1->get_component<TransformComponent>();
		other_tc_ = &player2->get_component<TransformComponent>();

		priority_cc_ = &player1->get_component<ColliderComponent>();
		other_cc_ = &player2->get_component<ColliderComponent>();
	}

	bool check_winner();
	bool check_match_winner();
	bool check_for_out_right_victor();
	bool check_attack_in_range(const Attack att);
	bool check_attack_in_range(const Attack att, const float updated_position);

	Attack check_attack_winner(const Attack p_p_att, const Attack o_p_att);
	void clean_up_round(PlayerComponent * winning_player)
	{
		winning_player->round_win();

		std::cout << winning_player->player_identity.id << " wins the round!" << std::endl;

		priority_pc_->change_priority();
		other_pc_->change_priority();
	}
};