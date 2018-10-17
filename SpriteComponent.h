#pragma once

#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"
#include "Animation.h"
#include <map>




class SpriteComponent : public Component
{
	TransformComponent * transform_;
	SDL_Texture *texture_;
	SDL_Rect src_rect_, dest_rect_;
	std::string anim_id_;
	int frames_ = 1;
	int speed_ = 200;
	int rotations_ = 0;

public:


	bool animated = false;
	int anim_index = 0;

	std::map<const char*, Animation > animations;

	SDL_RendererFlip sprite_flip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	SpriteComponent(const std::string id)
	{
		set_tex(id);
	}

	SpriteComponent(const std::string id, const int rots, const SDL_RendererFlip flp, const bool is_animated )
	{
		rotations_ = rots;
		sprite_flip = flp;
		set_tex(id);
		animated = is_animated;

		auto idle = Animation(0, 3, speed_);
		auto walk_left = Animation(1, 3, speed_);
		auto walk_right = Animation(2, 3, speed_);

		animations.emplace("idle", idle);
		animations.emplace("walk left", walk_left);
		animations.emplace("walk right", walk_right);
		play("idle");

	}

	SpriteComponent(const std::string id, const bool is_animated)
	{
		animated = is_animated;
		set_tex(id);
		auto idle = Animation(0, 3, speed_);
		auto  walk_right= Animation(1, 3, speed_);
		auto walk_left = Animation(2, 3, speed_);

		animations.emplace("idle", idle);
		animations.emplace("walk left", walk_left);
		animations.emplace("walk right", walk_right);
		play("idle");
	
	}

	~SpriteComponent()
	{
	}

	void set_tex(const std::string id)
	{
		texture_ = Game::assets->get_texture(id);
	}


	bool is_anim_id(const std::string a_id) const
	{
		return anim_id_ == a_id;
	}

	SDL_Rect clone_and_return_dest_rect(const int w) const
	{
		SDL_Rect clone_rect;
		clone_rect.y = dest_rect_.y;
		clone_rect.x = dest_rect_.x;
		clone_rect.w = w;
		clone_rect.h = dest_rect_.h;
		return clone_rect;
	}

	void init() override
	{
		transform_ = &entity->get_component<TransformComponent>();

		src_rect_.x = src_rect_.y = 0;
		src_rect_.w = transform_->width;
		src_rect_.h = transform_->height;
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
		TextureManager::draw(texture_, src_rect_, dest_rect_, rotations_, sprite_flip);
	}

	void play(const char* anim_name)
	{
		anim_id_ = anim_name;
		frames_ = animations[anim_name].frames;
		anim_index = animations[anim_name].index;
		speed_ = animations[anim_name].speed;
	}
};