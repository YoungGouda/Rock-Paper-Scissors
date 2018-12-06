#include "stdafx.h"
#include <cmath>


//bool EndOfRound::check_winner()
//{
//	auto is_winner = false;
//
//	const auto scaled_player = priority_tc_->scale * SPRITE_LENGTH;
//
//	if (check_for_out_right_victor())
//		is_winner = true;
//	else
//	{
//		// simulates the priority player whiffing its attack and doing a re-check to see if the other player wins on the whiff
//		if (check_attack_in_range(other_pc_->chosen_attack, priority_pc_->chosen_attack.whiff_distance * scaled_player))
//		{
//			clean_up_round(other_pc_);
//			is_winner = true;
//		}
//	}
//	return is_winner;
//}
//
//bool EndOfRound::check_match_winner()
//{
//	auto is_match_winner = false;
//	if (priority_pc_->num_wins == ROUNDWIN)
//		is_match_winner = true;
//	if (priority_pc_->num_wins == ROUNDWIN)
//		is_match_winner = true;
//	return is_match_winner;
//}
//
//
//
//bool EndOfRound::check_for_out_right_victor()
//{
//	auto p_p_att = priority_pc_->chosen_attack;
//	auto o_p_att = other_pc_->chosen_attack;
//	auto out_right_victor = false;
//
//	// checks for an exception where the other players jump kick is shorter than the whip of the priority player
//	const auto short_jump_kick_exception = p_p_att.attack_id == Whip && o_p_att.attack_id == Jump_Kick && !check_attack_in_range(o_p_att);
//
//	//checks if either attack is in range and if the priority player wins the exchange
//	if ( (check_attack_in_range(p_p_att) || check_attack_in_range(o_p_att)) && p_p_att.attack_id == check_attack_winner(p_p_att, o_p_att).attack_id)
//	{	
//		clean_up_round(priority_pc_);
//		out_right_victor = true;
//	}
//	else if ( (check_attack_in_range(p_p_att) || check_attack_in_range(o_p_att)) && o_p_att.attack_id == check_attack_winner(p_p_att, o_p_att).attack_id)
//	{
//		if(!short_jump_kick_exception)
//		{
//			clean_up_round(other_pc_);
//			out_right_victor = true;
//		}
//	}
//	return out_right_victor;
//}
//
//bool EndOfRound::check_attack_in_range(const Attack att)
//{
//	const auto player_distance = priority_cc_->collider.x - other_cc_->collider.x;
//	const auto att_range = att.range * priority_tc_->width * priority_tc_->scale;
//
//	return att_range >= std::abs(player_distance);
//}
//
//bool EndOfRound::check_attack_in_range(const Attack att, const float updated_position)
//{
//	const auto player_distance = priority_cc_->collider.x - other_cc_->collider.x;
//	const auto att_range = att.range * priority_tc_->width * priority_tc_->scale;
//
//	return att_range >= std::abs(player_distance) - updated_position;
//}
//
//
//Attack EndOfRound::check_attack_winner(const Attack p_p_att, const Attack o_p_att)
//{
//	auto winner = p_p_att;
//
//	if (p_p_att.attack_id == Whip)
//	{
//		if (o_p_att.attack_id == Jump_Kick)
//			winner = o_p_att;
//	}
//	if (p_p_att.attack_id == Jump_Kick)
//	{
//		if (o_p_att.attack_id == Grab)
//			winner = o_p_att;
//	}
//	if (p_p_att.attack_id == Grab)
//	{
//		if (o_p_att.attack_id == Whip)
//			winner = o_p_att;
//	}
//	return winner;
//}




