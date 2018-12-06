#pragma once

#include "ECS.h"
#include "SDL.h"
#include "Game.h"


class BoxComponent : public Component
{
	SDL_Texture * texture_;
public:
	SDL_Rect box_rect{};

	BoxComponent()
		= default;

	BoxComponent(const int scale)
		: scale_(scale)
	{
	}

	BoxComponent(SDL_Rect box_rect, const int scale)
		: box_rect(box_rect), scale_(scale)
	{
	}

	~BoxComponent()
	{}

	void init() override
	{
		if(entity->has_component<OptionsComponent>())
		{
			build_box(entity->get_component<OptionsComponent>().current_options->option_rect);
		}
		else { build_box(box_rect); }

		texture_ = entity->get_component<MultiTextureComponent>().texture_map["box"];
	}

	void build_box(const SDL_Rect box)
	{
		const auto scaled_size = BOX_SIZE * scale_;
		const auto box_w = box.w;
		const auto box_h = box.h;
		const auto left_x = box.x;
		const auto top_y = box.y;
		const auto right_x = box.x + box_w;
		const auto bot_y = box.y + box_h;

		//Top Left Corner
		box_rects_.push_back(SDL_Rect{ 0 , 0, BOX_SIZE, BOX_SIZE });
		box_rects_.push_back(SDL_Rect{ left_x, top_y, scaled_size, scaled_size });

		//Top Right Corner
		box_rects_.push_back(SDL_Rect{ BOX_SIZE * 2, 0, BOX_SIZE, BOX_SIZE });;
		box_rects_.push_back(SDL_Rect{ right_x, top_y, scaled_size, scaled_size });

		//Bot Left Corner
		box_rects_.push_back(SDL_Rect{ 0, BOX_SIZE * 2, BOX_SIZE, BOX_SIZE });
		box_rects_.push_back(SDL_Rect{ left_x, bot_y, scaled_size, scaled_size });

		//Bot Right Corner
		box_rects_.push_back(SDL_Rect{ BOX_SIZE * 2, BOX_SIZE * 2, BOX_SIZE, BOX_SIZE });
		box_rects_.push_back(SDL_Rect{ right_x, bot_y, scaled_size, scaled_size });

		//Top Side
		box_rects_.push_back(SDL_Rect{ BOX_SIZE, 0, BOX_SIZE, BOX_SIZE });
		box_rects_.push_back(SDL_Rect{left_x + scaled_size, top_y, box_w - scaled_size, scaled_size  });

		//Left Side
		box_rects_.push_back(SDL_Rect{ 0, BOX_SIZE, BOX_SIZE, BOX_SIZE });
		box_rects_.push_back(SDL_Rect{ left_x, top_y + scaled_size, scaled_size, box_h - scaled_size });

		//Right Side
		box_rects_.push_back(SDL_Rect{ BOX_SIZE * 2, BOX_SIZE, BOX_SIZE, BOX_SIZE });
		box_rects_.push_back(SDL_Rect{ right_x, top_y + scaled_size, scaled_size, box_h - scaled_size });

		//Bot Side
		box_rects_.push_back(SDL_Rect{ BOX_SIZE, BOX_SIZE * 2, BOX_SIZE, BOX_SIZE });
		box_rects_.push_back(SDL_Rect{ left_x + scaled_size, bot_y, box_w - scaled_size, scaled_size });

		//Body
		box_rects_.push_back(SDL_Rect{ BOX_SIZE, BOX_SIZE, BOX_SIZE, BOX_SIZE });
		box_rects_.push_back(SDL_Rect{ left_x + scaled_size, top_y + scaled_size,box_w - scaled_size, box_h - scaled_size });
	}


	void draw() override
	{
		for (auto i = 0; i < box_rects_.size(); i += 2)
		{
			TextureManager::draw(texture_, box_rects_[i], box_rects_[i + 1], 0, SDL_FLIP_NONE);
		}
	}

private:
	std::vector<SDL_Rect> box_rects_;
	int scale_;
};