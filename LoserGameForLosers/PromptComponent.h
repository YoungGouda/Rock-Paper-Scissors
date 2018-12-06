#pragma once
#include "ECS.h"
#include "Game.h"
#include "Components.h"

class PromptComponent : public Component
{
	SDL_Texture * tex_;
	SDL_Rect src_rect_, dest_rect_;
	TransformComponent * transform_;
public:

	PromptComponent(int src_x, int src_y, int src_w, int src_h)
	{
		src_rect_.x = src_x;
		src_rect_.y = src_y;
		src_rect_.w = src_w;
		src_rect_.h = src_h;
	}

	void init() override
	{
		transform_ = &entity->get_component<TransformComponent>();
		tex_ = entity->get_component<TextureComponent>().texture;
	}

	void update() override
	{
		dest_rect_.x = static_cast<int>(transform_->position.x);
		dest_rect_.y = static_cast<int>(transform_->position.y);
		dest_rect_.w = transform_->width * transform_->scale;
		dest_rect_.h = transform_->height * transform_->scale;
	}

	void draw() override
	{
		TextureManager::draw(tex_, src_rect_, dest_rect_, 0, SDL_FLIP_NONE);
	}
};