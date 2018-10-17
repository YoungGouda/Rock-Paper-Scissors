#pragma once
#include "Components.h"
#include "Attack.h"

class EndOfRoundLogic
{
public:
	EndOfRoundLogic() = default;

	EndOfRoundLogic(Entity * player1, Entity * player2)
	{
		p_player_tc_ = &player1->get_component<TransformComponent>();
		o_player_tc_ = &player2->get_component<TransformComponent>();

		p_player_pc_ = &player1->get_component<PlayerComponent>();
		o_player_pc_ = &player2->get_component<PlayerComponent>();

		p_player_sc_ = &player1->get_component<SpriteComponent>();
		o_player_sc_ = &player2->get_component<SpriteComponent>();
		if (player2->get_component<PlayerComponent>().priority_player)
		{
			p_player_tc_ = &player2->get_component<TransformComponent>();
			o_player_tc_ = &player1->get_component<TransformComponent>();

			p_player_pc_ = &player2->get_component<PlayerComponent>();
			o_player_pc_ = &player1->get_component<PlayerComponent>();

			p_player_sc_ = &player2->get_component<SpriteComponent>();
			o_player_sc_ = &player1->get_component<SpriteComponent>();
		}
	}
	~EndOfRoundLogic()
	= default;

	bool check_winner() const;
	bool check_match_winner() const;

	static Attack check_attack_winner(Attack p_p_att, Attack o_p_att);
private:
	TransformComponent * p_player_tc_;
	TransformComponent * o_player_tc_;
	SpriteComponent * p_player_sc_;
	SpriteComponent * o_player_sc_;
	PlayerComponent * p_player_pc_;
	PlayerComponent * o_player_pc_;
	bool check_for_out_right_victor(Attack p_p_att, Attack o_p_att) const;
	bool check_attack_in_range(Attack att) const;
	bool check_attack_in_range(Attack att, float updated_position) const;
	void clean_up_round(PlayerComponent * w_player_pc) const
	{
		std::cout << "Round Winner: " << w_player_pc->player_name << std::endl;
		if (check_match_winner())
			std::cout << "Congratulations " << w_player_pc->player_name << std::endl;
	}
};