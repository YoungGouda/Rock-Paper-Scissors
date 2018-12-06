#pragma once
#include "ECS.h"

class CursorComponent : public Component
{
public:

	CursorComponent(const float angle, const SDL_RendererFlip flip)
		: angle_(angle), cursor_flip_(flip)
	{
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

		texture_ = entity->get_component<MultiTextureComponent>().texture_map["cursor"];
	}


	void update() override
	{
		dest_ = options_->get_current_link()->get_cursor_dimensions();
	}

	void draw() override
	{
		TextureManager::draw(texture_, src_, dest_, angle_, cursor_flip_);
	}

private:
	OptionsComponent * options_;
	SDL_Rect dest_, src_;
	SDL_Texture * texture_;
	float angle_;
	SDL_RendererFlip cursor_flip_;
};
