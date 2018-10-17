#pragma once
#include "ECS.h"
#include "SDL.h"
#include "TextureManager.h"
#include "Components.h"

class MenuComponent : public Component
{
private:
	TransformComponent * transform_{};
	SDL_Texture *texture_{};
	SDL_Rect src_rect_{}, dest_rect_{}, left_dest_rect_{}, right_dest_rect_{};
	int rotations_ = 0;

public:


	SDL_RendererFlip sprite_flip = SDL_FLIP_NONE;

	MenuComponent() = default;

	explicit MenuComponent(const std::string& id)
	{
		set_tex(id);
	}

	MenuComponent(const std::string& id, const int rots, const SDL_RendererFlip flp)
	{
		rotations_ = rots;
		set_tex(id);
		sprite_flip = flp;
	}

	~MenuComponent()
	= default;

	void set_tex(const std::string& id)
	{
		texture_ = Game::assets->get_texture(id);
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
		dest_rect_.x = static_cast<int>(transform_->position.x);
		dest_rect_.y = static_cast<int>(SCREEN_HEIGHT - transform_->height * transform_->scale);
		dest_rect_.w = transform_->width * transform_->scale;
		dest_rect_.h = transform_->height * transform_->scale;
	}

	void draw() override
	{
		TextureManager::draw(texture_, src_rect_, dest_rect_, rotations_, sprite_flip);
	}
};