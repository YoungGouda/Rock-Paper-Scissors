#include "stdafx.h"

/**
 * Background
 **
 * In charge of manipulating the background based on the positions of the two players
 * 
 */


void Background::screen_change()
{
	// values for which the 
	auto scroll_inc = 0.0f;
	auto scale_inc = 0.0f;
	auto external_velocity_p1 = 0.0f;
	auto external_velocity_p2 = 0.0f;

	const auto p1_vec = p1_pc_->get_velocity() * p1_tc_->speed;
	const auto p2_vec = p2_pc_->get_velocity() * p2_tc_->speed;

	if (Collision::aabb(p1_col_c_->collider, LEFT_EDGE))
	{
		if (p1_tc_->position.x < LEFT_EDGE.x)
			p1_tc_->position.x = LEFT_EDGE.x;

		if (p1_tc_->player_velocity.x < 0)
		{	
			scale_inc -= p1_vec;
			if (!Collision::aabb(p2_col_c_->collider, RIGHT_EDGE))
			{
				scale_inc = 0;
				scroll_inc -= p1_vec;
				external_velocity_p2 += p1_pc_->get_velocity();
			}
			else if (p2_tc_->player_velocity.x < 0)
				scroll_inc -= p1_vec;
		}
		if (p1_tc_->player_velocity.x > 0)
		{
			scale_inc += p1_vec;
		}
	}
	if (Collision::aabb(p2_col_c_->collider, RIGHT_EDGE))
	{
		if (p2_tc_->position.x > RIGHT_EDGE.x + RIGHT_EDGE.w - static_cast<float>(p2_tc_->width) * p2_tc_->scale)
			p2_tc_->position.x = RIGHT_EDGE.x + RIGHT_EDGE.w - static_cast<float>(p2_tc_->width) * p2_tc_->scale;

		if (p2_tc_->player_velocity.x > 0)
		{
			scale_inc -= p2_vec;
			if (!Collision::aabb(p1_col_c_->collider, LEFT_EDGE))
			{
				external_velocity_p1 -= p2_pc_->get_velocity();
				scale_inc = 0;
				scroll_inc += p2_vec;
			}
			else if (p1_tc_->player_velocity.x > 0)
				scroll_inc += p2_vec;
		}
		if (p2_tc_->player_velocity.x < 0)
		{
			scale_inc += p2_vec;
		}
	}
	/*std::cout << "p1 ext vel : " << external_velocity_p1 << ", p2 ext vel : " << external_velocity_p2 << ", scroll_inc : " << scroll_inc << ", scale_inc " << scale_inc << std::endl;
*/
	p1_tc_->external_velocity.x = external_velocity_p1;
	p2_tc_->external_velocity.x = external_velocity_p2;

	scroll_screen(scroll_inc);
	scale_screen(scale_inc);
}

void Background::scroll_screen(float scroll_increment)
{
	bg_tc_->position.x = (bg_tc_->position.x - scroll_increment * p1_tc_->scale / SPRITE_SCALING);
	if (!(bg_tc_->position.x > -bg_tc_->width * bg_tc_->scale && bg_tc_->position.x < bg_tc_->width * bg_tc_->scale))
		bg_tc_->position.x = (0);

}

void Background::scale_screen(float scale_increment)
{
	// the difference between scale bounds / the possible distance traveled by a single character * stretch speed
	const auto player_sc_range = (SPRITE_SCALING - SPRITE_SCALING_TARGET) / static_cast<float>(SCREEN_WIDTH - SPRITE_SCALED) * scale_increment * p1_tc_->scale / SPRITE_SCALING;
	const auto background_sc_range = (BACKGROUND_SCALING - BACKGROUND_SCALING_TARGET) / static_cast<float>(SCREEN_WIDTH - SPRITE_SCALED) * scale_increment * bg_tc_->scale / BACKGROUND_SCALING;

	p1_tc_->scale = std::min(std::max(SPRITE_SCALING_TARGET, p1_tc_->scale + player_sc_range), SPRITE_SCALING);
	p1_tc_->position.y = SCREEN_HEIGHT - p1_tc_->height * p1_tc_->scale;

	auto scaling_offset_x = p2_tc_->scale - p1_tc_->scale;

	p2_tc_->scale = p1_tc_->scale;
	p2_tc_->position.x = p2_tc_->position.x + scaling_offset_x * p2_tc_->width;
	p2_tc_->position.y = SCREEN_HEIGHT - p1_tc_->height * p1_tc_->scale;


	auto previous_scale = bg_tc_->scale;

	bg_tc_->scale = std::min(std::max(BACKGROUND_SCALING_TARGET, bg_tc_->scale + background_sc_range), BACKGROUND_SCALING);
	scaling_offset_x = previous_scale - bg_tc_->scale;


	// this is probably a formula somewhere
	auto center_of_scaling = SCREEN_WIDTH * (0.5 + (p1_pc_->get_velocity() - p2_pc_->get_velocity()) / 2);

	if (std::fabsf(p1_tc_->player_velocity.x) <= FLT_EPSILON)
		center_of_scaling = 0;
	if (std::fabsf(p2_tc_->player_velocity.x) <= FLT_EPSILON)
		center_of_scaling = SCREEN_WIDTH;

	// the difference in scaling from new and old backgrounds * the background width * the center of scaling
	bg_tc_->position.x += scaling_offset_x * bg_tc_->width * (-bg_tc_->position.x + center_of_scaling) / (BACKGROUND_WIDTH * bg_tc_->scale);
	bg_tc_->position.y = SCREEN_HEIGHT - bg_tc_->height * bg_tc_->scale;
}

