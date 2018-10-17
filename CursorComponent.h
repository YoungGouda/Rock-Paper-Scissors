#pragma once
#include "ECS.h"

class CursorComponent : public Component
{
public:

	CursorComponent(const std::string cursor_id, const int rots, const SDL_RendererFlip flip)
		: link_x_(0), link_y_(0), rotations_(rots), cursor_flip_(flip)
	{
		texture_ = Game::assets->get_texture(cursor_id);

		src_.x = src_.y = 0;
	}

	~CursorComponent()
	{}

	void init() override
	{
		if (entity->has_component<OptionsComponent>())
		{
			options_ = &entity->get_component<OptionsComponent>();

			dest_ = options_->get_current_link()->get_cursor_dimensions();
			src_.w = options_->get_current_link()->get_cursor_dimensions().w;
			src_.h = options_->get_current_link()->get_cursor_dimensions().h;
		}
	}


	void update() override
	{
		dest_ = options_->get_current_link()->get_cursor_dimensions();
	}

	void draw() override
	{
		TextureManager::draw(texture_, src_, dest_, rotations_, cursor_flip_);
	}

private:
	OptionsComponent * options_;
	int link_x_;
	int link_y_;
	int next_x_ = 0;
	int next_y_ = 0;
	SDL_Rect dest_, src_;
	std::vector<std::vector<Link *>> links_;
	SDL_Texture * texture_;
	int rotations_;
	SDL_RendererFlip cursor_flip_;
};
