#include "stdafx.h"
#include "EndOfRoundLogic.h"
#include <cmath>

bool EndOfRoundLogic::check_winner() const
{
	auto is_winner = false;

	const auto scaled_player = p_player_tc_->scale * SPRITE_LENGTH;

	if (check_for_out_right_victor(p_player_pc_->chosen_attack, o_player_pc_->chosen_attack))
		is_winner = true;
	else
	{
		// simulates the priority player whiffing its attack and doing a re-check to see if the other player wins on the whiff
		if (check_attack_in_range(o_player_pc_->chosen_attack, p_player_pc_->chosen_attack.whiff_distance * scaled_player))
		{
			clean_up_round(o_player_pc_);
			is_winner = true;
		}
	}
	return is_winner;
}

bool EndOfRoundLogic::check_match_winner() const
{
	auto is_match_winner = false;
	if (p_player_pc_->num_wins == ROUNDWIN)
		is_match_winner = true;
	if (o_player_pc_->num_wins == ROUNDWIN)
		is_match_winner = true;
	return is_match_winner;
}

bool EndOfRoundLogic::check_for_out_right_victor(const Attack p_p_att, const Attack o_p_att) const
{
	auto out_right_victor = false;

	// checks for an exception where the other players jump kick is shorter than the whip of the priority player
	const auto short_jump_kick_exception = p_p_att.attack_id == "whip" && o_p_att.attack_id == "jump kick" && !check_attack_in_range(o_p_att);

	//checks if either attack is in range and if the priority player wins the exchange
	if ( (check_attack_in_range(p_p_att) || check_attack_in_range(o_p_att)) && p_p_att.attack_id == check_attack_winner(p_p_att, o_p_att).attack_id)
	{	
		clean_up_round(p_player_pc_);
		out_right_victor = true;
	}
	else if ( (check_attack_in_range(p_p_att) || check_attack_in_range(o_p_att)) && o_p_att.attack_id == check_attack_winner(p_p_att, o_p_att).attack_id)
	{
		if(!short_jump_kick_exception)
		{
			clean_up_round(o_player_pc_);
			out_right_victor = true;
		}
	}
	return out_right_victor;
}

bool EndOfRoundLogic::check_attack_in_range(const Attack att) const
{
	const auto player_distance = p_player_pc_->get_player_distance() - o_player_pc_->get_player_distance();
	const auto att_range = att.range * p_player_tc_->width * p_player_tc_->scale;

	return att_range >= std::abs(player_distance);
}

bool EndOfRoundLogic::check_attack_in_range(const Attack att, const float updated_position) const
{
	const auto player_distance = p_player_pc_->get_player_distance() - o_player_pc_->get_player_distance();
	const auto att_range = att.range * p_player_tc_->width * p_player_tc_->scale;

	return att_range >= std::abs(player_distance) - updated_position;
}


Attack EndOfRoundLogic::check_attack_winner(const Attack p_p_att, const Attack o_p_att)
{
	auto winner = p_p_att;

	if (p_p_att.attack_id == "whip")
	{
		if (o_p_att.attack_id == "jump kick")
			winner = o_p_att;
	}
	if (p_p_att.attack_id == "jump kick")
	{
		if (o_p_att.attack_id == "grab")
			winner = o_p_att;
	}
	if (p_p_att.attack_id == "grab")
	{
		if (o_p_att.attack_id == "whip")
			winner = o_p_att;
	}
	return winner;
}
