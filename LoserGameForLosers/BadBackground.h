#pragma once
class BadBackground
{
public:
	BadBackground() = default;

	BadBackground(Entity * player1, Entity * player2, Entity * background, const int max_r) : max_range_(max_r)
	{
		p1_tc_ = &player1->get_component<TransformComponent>();
		p2_tc_ = &player2->get_component<TransformComponent>();
		bg_tc_ = &background->get_component<TransformComponent>();

		p1_pc_ = &player1->get_component<PlayerComponent>();
		p2_pc_ = &player2->get_component<PlayerComponent>();

		p1_sc_ = &player1->get_component<SpriteComponent>();
		p2_sc_ = &player2->get_component<SpriteComponent>();

		p1_col_c_ = &player1->get_component<ColliderComponent>();
		p2_col_c_ = &player2->get_component<ColliderComponent>();

		player1_velocity_scale_ = p1_pc_->get_velocity();
		player2_velocity_scale_ = p2_pc_->get_velocity();

		player1_velocity_scale_difference_ = player1_velocity_scale_ - player2_velocity_scale_;
		player2_velocity_scale_difference_ = player2_velocity_scale_ - player1_velocity_scale_;
	}

	~BadBackground()
	{}

	void screen_change(float prevPlayer1X, float prevPlayer2X) const;
	void scroll_screen_right(float scroll_increment) const;
	void scroll_screen_left(float scroll_increment) const;
	void stretch_assets(float stretch) const;
	void shrink_assets(float shrink) const;


private:
	TransformComponent * p1_tc_;
	TransformComponent * p2_tc_;
	TransformComponent * bg_tc_;

	PlayerComponent * p1_pc_;
	PlayerComponent * p2_pc_;

	SpriteComponent * p1_sc_;
	SpriteComponent * p2_sc_;

	ColliderComponent * p1_col_c_;
	ColliderComponent * p2_col_c_;

	int max_range_;

	float player1_velocity_scale_;
	float player2_velocity_scale_;

	float player1_velocity_scale_difference_;
	float player2_velocity_scale_difference_;

	const SDL_Rect LEFT_EDGE{ 0, 0, BACKGROUND_COLLIDER, BACKGROUND_HEIGHT };
	const SDL_Rect RIGHT_EDGE{ BACKGROUND_WIDTH - BACKGROUND_COLLIDER, 0, BACKGROUND_COLLIDER, BACKGROUND_HEIGHT };

};