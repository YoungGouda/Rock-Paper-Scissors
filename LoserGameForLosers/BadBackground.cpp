#include "BadBackground.h"

void BadBackground::screen_change(const float prev_player1_x, const float prev_player2_x) const
{
	const float left_edge = 0;
	const auto right_edge = static_cast<float>(SCREEN_WIDTH) - static_cast<float>(p2_tc_->width) * p2_tc_->scale;
	const int bottom = SCREEN_HEIGHT - p1_tc_->height * p1_tc_->scale;

	//Sets players to the edges of the screen if they move off the background
	if (p1_tc_->position.x < left_edge)
		p1_tc_->position.x = left_edge;
	if (p2_tc_->position.x > right_edge)
		p2_tc_->position.x = right_edge;
	p1_tc_->position.y = bottom;
	p2_tc_->position.y = bottom;

	// player direction checks
	const auto player1_walk_left = p1_sc_->is_anim_id(Walk_Left);
	const auto player1_walk_right = p1_sc_->is_anim_id(Walk_Right);
	const auto player1_idle = p1_sc_->is_anim_id(Idle);
	const auto player2_walk_left = p2_sc_->is_anim_id(Walk_Left);
	const auto player2_walk_right = p2_sc_->is_anim_id(Walk_Right);
	const auto player2_idle = p2_sc_->is_anim_id(Idle);

	// edge checks
	const auto player1_is_at_edge = p1_tc_->position.x < left_edge + FLT_EPSILON;
	auto player2_is_at_edge = p2_tc_->position.x >= right_edge - FLT_EPSILON;

	const auto players_distance = (p2_tc_->position.x - (static_cast<float>(p2_tc_->width) * p2_tc_->scale) * p2_pc_->player_identity.hit_box) -
		p1_tc_->position.x + (static_cast<float>(p1_tc_->width) * p1_tc_->scale) * p1_pc_->player_identity.hit_box;
	const auto is_max_range = players_distance / (static_cast<float>(p1_tc_->width) * p1_tc_->scale) > max_range_;



	// Stretch Assets
	if (
		player1_is_at_edge && player2_is_at_edge
		&& (player1_walk_left || player1_idle)
		&& (player2_walk_right || player2_idle)
		&& !(player1_idle && player2_idle)
		&& !is_max_range
		&& p1_tc_->scale > SPRITE_SCALING_TARGET && bg_tc_->scale > BACKGROUND_SCALING_TARGET
		)
	{
		/*std::cout << "STRETCH" << std::endl;*/
		auto stretch_speed = 0;
		// increments the speed of stretch based on whether the players are walking towards to edges of their screens
		if (player1_walk_left)
			stretch_speed += player1_velocity_scale_ * p1_tc_->speed;
		if (player2_walk_right)
			stretch_speed += player2_velocity_scale_ * p2_tc_->speed;
		stretch_assets(stretch_speed);
		// checks if its scrolled too far
		scroll_screen_left(0);

	}
	// Shrink Assets
	else if (
		(player1_walk_right && player2_idle
			|| player2_walk_left && player1_idle
			|| player1_walk_right && player2_walk_left)
		&& p1_tc_->scale < SPRITE_SCALING
		)
	{
		/*std::cout << "SHRINK" << std::endl;*/
		auto shrink_speed = 0;
		if (player1_walk_right)
			shrink_speed += player1_velocity_scale_ * p1_tc_->speed;
		if (player2_walk_left)
			shrink_speed += player2_velocity_scale_ * p2_tc_->speed;

		shrink_assets(shrink_speed);
	}
	//Scroll Background Left
	else if (
		player1_is_at_edge && player1_walk_left
		&& (!player2_is_at_edge || !player2_walk_right)
		&& p1_tc_->scale > SPRITE_SCALING_TARGET && bg_tc_->scale > BACKGROUND_SCALING_TARGET
		)
	{
		auto scroll_increment = 0.0f;
		if (player2_idle && !is_max_range && bg_tc_->scale > BACKGROUND_SCALING_TARGET)
		{
			scroll_increment = player1_velocity_scale_ * p1_tc_->speed;
			p2_tc_->position.x = (prev_player2_x + player1_velocity_scale_ * p1_tc_->speed * p1_tc_->scale / SPRITE_SCALING);
		}
		if (player2_walk_left)
		{
			scroll_increment = player1_velocity_scale_ * p1_tc_->speed;
			if (prev_player2_x - player2_velocity_scale_difference_ * p1_tc_->speed * p1_tc_->scale / SPRITE_SCALING < right_edge)
			{
				p2_tc_->position.x = (prev_player2_x - player2_velocity_scale_difference_ * p1_tc_->speed * p1_tc_->scale / SPRITE_SCALING);
			}
			else
				p2_tc_->position.x = (right_edge);
			player2_is_at_edge = p2_tc_->position.x >= right_edge - FLT_EPSILON;

			if (player2_velocity_scale_difference_ > 0)
				shrink_assets(player2_velocity_scale_difference_ * p2_tc_->speed);
			if (player1_velocity_scale_difference_ > 0 && player2_is_at_edge && !is_max_range && bg_tc_->scale > BACKGROUND_SCALING_TARGET)
				stretch_assets(player1_velocity_scale_difference_ * p1_tc_->speed);
		}
		if (player2_walk_right && !is_max_range && bg_tc_->scale > BACKGROUND_SCALING_TARGET)
		{
			scroll_increment = player1_velocity_scale_ * p1_tc_->speed;
			p2_tc_->position.x = (p2_tc_->position.x + player1_velocity_scale_ * p1_tc_->speed * p1_tc_->scale / SPRITE_SCALING);
		}
		scroll_screen_left(scroll_increment);
	}
	// Scroll Background Right
	else if (
		player2_is_at_edge && player2_walk_right
		&& (!player1_is_at_edge || !player1_walk_left)
		)
	{

		auto scroll_increment = 0.0f;
		if (player1_idle && !is_max_range && bg_tc_->scale > BACKGROUND_SCALING_TARGET)
		{
			scroll_increment = player2_velocity_scale_ * p2_tc_->speed;
			p1_tc_->position.x = (prev_player1_x - player2_velocity_scale_ * p2_tc_->speed * p1_tc_->scale / SPRITE_SCALING);
		}
		if (player1_walk_right)
		{
			scroll_increment = player1_velocity_scale_ * p1_tc_->speed;

			if (prev_player1_x + player1_velocity_scale_difference_ * p2_tc_->speed * p1_tc_->scale / SPRITE_SCALING > left_edge)
			{
				p1_tc_->position.x = (prev_player1_x);
				if (p1_tc_->scale >= SPRITE_SCALING)
					p1_tc_->position.x = (prev_player1_x + player1_velocity_scale_difference_ * p2_tc_->speed * p1_tc_->scale / SPRITE_SCALING);
			}
			else
				p1_tc_->position.x = (left_edge);
			if (player1_velocity_scale_difference_ > 0)
				shrink_assets(player1_velocity_scale_difference_ * p1_tc_->speed);
			if (player2_velocity_scale_difference_ > 0 && player1_is_at_edge && !is_max_range && bg_tc_->scale > BACKGROUND_SCALING_TARGET)
				stretch_assets(player2_velocity_scale_difference_ * p2_tc_->speed);
		}
		if (player1_walk_left && !is_max_range && bg_tc_->scale > BACKGROUND_SCALING_TARGET)
		{
			scroll_increment = player2_velocity_scale_ * p2_tc_->speed;
			p1_tc_->position.x = (p1_tc_->position.x - player2_velocity_scale_ * p2_tc_->speed * p1_tc_->scale / SPRITE_SCALING);
		}
		scroll_screen_right(scroll_increment);
	}
}

void BadBackground::scroll_screen_right(const float scroll_increment) const
{
	bg_tc_->position.x = (bg_tc_->position.x - scroll_increment * p1_tc_->scale / SPRITE_SCALING);
	if (bg_tc_->position.x < -bg_tc_->width * bg_tc_->scale)
		bg_tc_->position.x = (0);
}

void BadBackground::scroll_screen_left(const float scroll_increment) const
{
	bg_tc_->position.x = (bg_tc_->position.x + scroll_increment * p1_tc_->scale / SPRITE_SCALING);
	if (bg_tc_->position.x > bg_tc_->width * bg_tc_->scale)
		bg_tc_->position.x = (0);
}

void BadBackground::stretch_assets(const float stretch) const
{
	// the difference between scale bounds / the possible distance traveled by a single character * stretch speed
	const auto player_sc_range = (SPRITE_SCALING - SPRITE_SCALING_TARGET) / static_cast<float>(SCREEN_WIDTH - SPRITE_SCALED) * -stretch * p1_tc_->scale / SPRITE_SCALING;
	const auto background_sc_range = (BACKGROUND_SCALING - BACKGROUND_SCALING_TARGET) / static_cast<float>(SCREEN_WIDTH - SPRITE_SCALED) * -stretch * bg_tc_->scale / BACKGROUND_SCALING;

	p1_tc_->scale = std::max(SPRITE_SCALING_TARGET, p1_tc_->scale + player_sc_range);

	auto scaling_offset_x = p2_tc_->width * p2_tc_->scale - (p2_tc_->scale + player_sc_range) * p2_tc_->width;

	const auto player1_stretch = p1_sc_->is_anim_id(Walk_Left) && p2_sc_->is_anim_id(Idle);
	const auto player2_stretch = p2_sc_->is_anim_id(Walk_Right) && p1_sc_->is_anim_id(Idle);


	if (SPRITE_SCALING_TARGET < p2_tc_->scale)
		p2_tc_->position.x = p2_tc_->position.x + scaling_offset_x + 1;

	p2_tc_->scale = std::max(SPRITE_SCALING_TARGET, p2_tc_->scale + player_sc_range);

	scaling_offset_x = bg_tc_->width * bg_tc_->scale - (bg_tc_->scale + background_sc_range) * bg_tc_->width;

	bg_tc_->scale = std::max(BACKGROUND_SCALING_TARGET, bg_tc_->scale + background_sc_range);

	auto center_of_stretch = SCREEN_WIDTH * player1_velocity_scale_ * p1_tc_->speed / (player1_velocity_scale_ * p1_tc_->speed + player2_velocity_scale_ * p2_tc_->speed);

	if (player2_stretch)
		center_of_stretch = 0;
	if (player1_stretch)
		center_of_stretch = SCREEN_WIDTH;

	// the difference in scaling from new and old backgrounds * the center of stretch = goddamn stretching miracle
	if (BACKGROUND_SCALING_TARGET < bg_tc_->scale)
		bg_tc_->position.x = (
			bg_tc_->position.x + scaling_offset_x * (-bg_tc_->position.x + center_of_stretch) / (BACKGROUND_WIDTH * bg_tc_->scale)
			);
}

void BadBackground::shrink_assets(const float shrink) const
{
	// the difference between scale bounds / the possible distance traveled by a single character * stretch speed
	const auto player_sc_range = (SPRITE_SCALING - SPRITE_SCALING_TARGET) / static_cast<float>(SCREEN_WIDTH - SPRITE_SCALED) * shrink * p1_tc_->scale / SPRITE_SCALING;
	const auto background_sc_range = (BACKGROUND_SCALING - BACKGROUND_SCALING_TARGET) / static_cast<float>(SCREEN_WIDTH - SPRITE_SCALED) * shrink * bg_tc_->scale / BACKGROUND_SCALING;

	const auto player1_shrink = p1_sc_->is_anim_id(Walk_Right) && p2_sc_->is_anim_id(Idle);
	const auto player2_shrink = p2_sc_->is_anim_id(Walk_Left) && p1_sc_->is_anim_id(Idle);

	p1_tc_->scale = (std::min(SPRITE_SCALING, p1_tc_->scale + player_sc_range));

	auto scaling_offset_x = p2_tc_->width * p2_tc_->scale - (p2_tc_->scale + player_sc_range) * p2_tc_->width;


	// to account for stretching position changes
	if (SPRITE_SCALING_TARGET < p2_tc_->scale)
		p2_tc_->position.x = (p2_tc_->position.x + scaling_offset_x * (SPRITE_LENGTH * p2_tc_->scale) / (SPRITE_LENGTH * std::min(SPRITE_SCALING, p2_tc_->scale + player_sc_range)));

	p2_tc_->scale = (std::min(SPRITE_SCALING, p2_tc_->scale + player_sc_range));

	scaling_offset_x = bg_tc_->width * bg_tc_->scale - (bg_tc_->scale + background_sc_range) * bg_tc_->width;

	bg_tc_->scale = (std::min(BACKGROUND_SCALING, bg_tc_->scale + background_sc_range));

	auto center_of_stretch = SCREEN_WIDTH * player1_velocity_scale_ * p1_tc_->speed / (player1_velocity_scale_ * p1_tc_->speed + player2_velocity_scale_ * p2_tc_->speed);

	if (player2_shrink)
		center_of_stretch = 0;
	if (player1_shrink)
		center_of_stretch = SCREEN_WIDTH;

	// the difference in scaling from new and old backgrounds * the center of stretch = goddamn stretching miracle
	if (BACKGROUND_SCALING_TARGET < bg_tc_->scale)
		bg_tc_->position.x = (
			bg_tc_->position.x + scaling_offset_x * (-bg_tc_->position.x + center_of_stretch) / (BACKGROUND_WIDTH * bg_tc_->scale)
			);
}