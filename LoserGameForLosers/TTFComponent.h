#pragma once

#include "ECS.h"
#include "AssetManager.h"
#include "Game.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>


struct TTFLabel
{
	TTFLabel(const SDL_Rect pos, SDL_Texture * tex)
		: position(pos), texture(tex)
	{}
	~TTFLabel() = default;
	SDL_Rect position;
	SDL_Texture * texture;
};

class TTFComponent : public Component
{
public:

	TTFComponent(SDL_Color& color)
		: text_color_(color)
	{}

	TTFComponent(const int x, const int y, const std::string text, const std::string font, SDL_Color& color) 
		: text_color_(color)
	{
		position_ = SDL_Rect{ x, y, 0, 0 };

		set_label_text(text.c_str(), position_, font.c_str());
	}
	~TTFComponent()
	= default;

	void init() override
	{
		if(entity->has_component<OptionsComponent>())
		{
			for( auto& x_link : entity->get_component<OptionsComponent>().current_options->option_links)
			{
				for(auto& y_link : x_link)
				{
					set_label_text(y_link);
				}
			}
		}
	}

	void set_label_text(std::string text, SDL_Rect position, const std::string font)
	{
		const auto surf = TTF_RenderText_Blended(Game::assets->get_font(font), text.c_str(), text_color_);
		const auto label_texture = SDL_CreateTextureFromSurface(Game::renderer, surf);
		SDL_FreeSurface(surf);

		SDL_QueryTexture(label_texture, nullptr, nullptr, &position.w, &position.h);

		label_creator_.push_back(new TTFLabel(position, label_texture));
	}

	void set_label_text(Link * link)
	{
		SDL_Surface* surf = TTF_RenderText_Blended(Game::assets->get_font(link->get_font()), link->get_text().c_str(), text_color_);
		SDL_Texture* label_texture = SDL_CreateTextureFromSurface(Game::renderer, surf);
		SDL_FreeSurface(surf);


		label_creator_.push_back(new TTFLabel(link->get_link_dimensions(), label_texture));
	}

	void draw() override
	{
		for (auto& label : label_creator_)
		{
			SDL_RenderCopy(Game::renderer, label->texture, nullptr, &label->position);
		}
	}

private:
	SDL_Rect position_;
	std::vector<TTFLabel *> label_creator_;
	std::string label_text_;
	std::string label_font_;
	SDL_Color text_color_;
};