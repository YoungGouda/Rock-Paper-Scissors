#pragma once
#pragma once
#include "ECS.h"

class MultiTextureComponent : public Component
{
	Uint8 alpha_, red_, green_, blue_;

public:

	std::map<std::string, SDL_Texture *> texture_map;

	MultiTextureComponent(std::vector<std::string> textures)
	{
		for (auto t : textures)
		{
			add_texture(t);
		}
	}

	~MultiTextureComponent() {}


	void add_texture(std::string tex)
	{
		texture_map.try_emplace(tex, Game::assets->get_texture(tex));
	}

	void set_alpha(Uint8 alpha)
	{
		alpha_ = alpha;
		for (auto t : texture_map)
		{
			SDL_SetTextureAlphaMod(t.second, alpha_);
		}
	}

	void increment_alpha(Uint8 increment)
	{
		alpha_ += increment;
		for (auto t : texture_map)
		{
			SDL_SetTextureAlphaMod(t.second, alpha_);
		}
	}

	void set_blend_mode(SDL_BlendMode blending)
	{
		for (auto t : texture_map)
		{
			SDL_SetTextureBlendMode(t.second, blending);
		}
	}

	void set_rgb(Uint8 red, Uint8 green, Uint8 blue)
	{
		for (auto t : texture_map)
		{
			SDL_SetTextureColorMod(t.second, red, green, blue);
		}
	}


};
