#pragma once

#include "ECS.h"
#include "SDL.h"
#include "Game.h"


class BoxComponent : public Component
{
public:
	SDL_Texture * texture;
	SDL_Rect box_rect{};

	BoxComponent()
		= default;

	BoxComponent(const int scale, const std::string id)
		: scale_(scale)
	{
		texture = Game::assets->get_texture(id);
	}

	BoxComponent(const SDL_Rect box_rect, const int scale, const std::string id)
		: box_rect(box_rect), scale_(scale)
	{
		texture = Game::assets->get_texture(id);
	}

	~BoxComponent()
	{
		SDL_DestroyTexture(texture);
	}
	void init() override
	{
		if(entity->has_component<OptionsComponent>())
		{
			build_box(entity->get_component<OptionsComponent>().current_options->option_rect);
		}
		else { build_box(box_rect); }

	}

	void build_box(const SDL_Rect box)
	{
		const int scaled_size = BOX_SIZE * scale_;
		const int box_w = box.w;
		const int box_h = box.h;
		const int left_x = box.x;
		const int top_y = box.y;
		const int right_x = box.x + box_w;
		const int bot_y = box.y + box_h;

		//Top Left Corner
		src_top_left_corner_ = { 0 , 0, BOX_SIZE, BOX_SIZE };
		dest_top_left_corner_ = { left_x, top_y, scaled_size, scaled_size };

		//Top Right Corner
		src_top_right_corner_ = { BOX_SIZE * 2, 0, BOX_SIZE, BOX_SIZE };
		dest_top_right_corner_ = { right_x, top_y, scaled_size, scaled_size };

		//Bot Left Corner
		src_bot_left_corner_ = { 0, BOX_SIZE * 2, BOX_SIZE, BOX_SIZE };
		dest_bot_left_corner_ = { left_x, bot_y, scaled_size, scaled_size };

		//Bot Right Corner
		src_bot_right_corner_ = { BOX_SIZE * 2, BOX_SIZE * 2, BOX_SIZE, BOX_SIZE };
		dest_bot_right_corner_ = { right_x, bot_y, scaled_size, scaled_size };

		//Top Side
		src_top_ = { BOX_SIZE, 0, BOX_SIZE, BOX_SIZE };
		dest_top_ = {left_x + scaled_size, top_y, box_w - scaled_size, scaled_size  };

		//Left Side
		src_left_ = { 0, BOX_SIZE, BOX_SIZE, BOX_SIZE };
		dest_left_ = { left_x, top_y + scaled_size, scaled_size, box_h - scaled_size };

		//Right Side
		src_right_ = { BOX_SIZE * 2, BOX_SIZE, BOX_SIZE, BOX_SIZE };
		dest_right_ = { right_x, top_y + scaled_size, scaled_size, box_h - scaled_size };

		//Bot Side
		src_bot_ = { BOX_SIZE, BOX_SIZE * 2, BOX_SIZE, BOX_SIZE };
		dest_bot_ = { left_x + scaled_size, bot_y, box_w - scaled_size, scaled_size };

		//Body
		src_body_ = { BOX_SIZE, BOX_SIZE, BOX_SIZE, BOX_SIZE };
		dest_body_ = { left_x + scaled_size, top_y + scaled_size,box_w - scaled_size, box_h - scaled_size };
	}

	void update() override
	{}

	void draw() override
	{
		TextureManager::draw(texture, src_top_left_corner_, dest_top_left_corner_, rotations_, flip_);
		TextureManager::draw(texture, src_top_right_corner_, dest_top_right_corner_, rotations_, flip_);
		TextureManager::draw(texture, src_bot_left_corner_, dest_bot_left_corner_, rotations_, flip_);
		TextureManager::draw(texture, src_bot_right_corner_, dest_bot_right_corner_, rotations_, flip_);
		TextureManager::draw(texture, src_top_, dest_top_, rotations_, flip_);
		TextureManager::draw(texture, src_left_, dest_left_, rotations_, flip_);
		TextureManager::draw(texture, src_right_, dest_right_, rotations_, flip_);
		TextureManager::draw(texture, src_bot_, dest_bot_, rotations_, flip_);
		TextureManager::draw(texture, src_body_, dest_body_, rotations_, flip_);
	}

private:
	SDL_Rect src_top_left_corner_, src_top_, src_top_right_corner_, src_right_, src_bot_right_corner_, src_bot_, src_bot_left_corner_, src_left_, src_body_;
	SDL_Rect dest_top_left_corner_, dest_top_, dest_top_right_corner_, dest_right_, dest_bot_right_corner_, dest_bot_, dest_bot_left_corner_, dest_left_, dest_body_;
	int scale_;
	SDL_RendererFlip flip_ = SDL_FLIP_NONE;
	int rotations_ = 0;

};