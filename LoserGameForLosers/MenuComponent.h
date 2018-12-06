#pragma once
#include "ECS.h"
#include "SDL.h"
#include "TextureManager.h"
#include "Components.h"

class MenuComponent : public Component
{
private:
	TransformComponent * transform_{};
	SDL_Texture * texture_{};
	SDL_Rect src_rect_{}, dest_rect_{};

public:

	MenuComponent() = default;

	~MenuComponent()
	{}

	void init() override
	{
		transform_ = &entity->get_component<TransformComponent>();

		texture_ = entity->get_component<TextureComponent>().texture;
		src_rect_.x = src_rect_.y = 0;
		src_rect_.w = dest_rect_.w = transform_->width;
		src_rect_.h = dest_rect_.h = transform_->height;
	}

	void draw() override
	{
		TextureManager::draw(texture_, src_rect_, dest_rect_, 0, SDL_FLIP_NONE);
	}
};