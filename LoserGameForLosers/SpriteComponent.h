#pragma once

#include "SDL.h"
#include "Animation.h"


class SpriteComponent : public Component
{
	TransformComponent * transform_;
	SDL_Rect src_rect_, dest_rect_;
	int frames_ = 1;
	int speed_ = 200;
	ANIMATIONS current_animation_;
	float angle_ = 0;
	SDL_Texture * texture_;
public:

	bool animated = false;
	int anim_index = 0;

	std::vector<Animation> animations;

	SDL_RendererFlip sprite_flip = SDL_FLIP_NONE;

	SpriteComponent() = default;

	SpriteComponent(const float angle, const SDL_RendererFlip flp, const bool is_animated )
	{
		angle_ = angle;
		sprite_flip = flp;
		animated = is_animated;

	}

	SpriteComponent(const bool is_animated)
	{
		animated = is_animated;
	}

	~SpriteComponent()
	{
	}
 


	void init() override
	{
		transform_ = &entity->get_component<TransformComponent>();

		texture_ = entity->get_component<TextureComponent>().texture;
		src_rect_.x = src_rect_.y = 0;
		src_rect_.w = transform_->width;
		src_rect_.h = transform_->height;

		if (sprite_flip == SDL_FLIP_HORIZONTAL)
		{
			entity->get_component<PlayerComponent>().direction = -1;
		}

		if (animated)
		{
			const auto idle = Animation(0, 3, speed_);
			const auto walk_right = Animation(1, 3, speed_);
			const auto walk_left = Animation(2, 3, speed_);

			animations.push_back(idle);
			animations.push_back(walk_right);
			animations.push_back(walk_left);

			play(Idle);
		}
	}
	void update() override
	{
		if (animated)
		{
			src_rect_.x = src_rect_.w * static_cast<int>((SDL_GetTicks() / speed_) % frames_);
		}
			
		src_rect_.y = anim_index * transform_->height;

		dest_rect_.x = static_cast<int>(transform_->position.x);
		dest_rect_.y = static_cast<int>(transform_->position.y);
		dest_rect_.w = transform_->width * transform_->scale;
		dest_rect_.h = transform_->height * transform_->scale;
	}

	void draw() override
	{
		TextureManager::draw(texture_, src_rect_, dest_rect_, angle_, sprite_flip);
	}

	void play(const ANIMATIONS animation)
	{
		current_animation_ = animation;
		frames_ = animations[animation].frames;
		anim_index = animations[animation].index;
		speed_ = animations[animation].speed;
	}
};