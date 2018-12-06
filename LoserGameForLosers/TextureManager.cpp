#include "stdafx.h"
#include "TextureManager.h"
#include "Constants.h"

SDL_Texture* TextureManager::load_texture(const char* texture)
{
	const auto temp_surface = IMG_Load(texture);
	const auto tex = SDL_CreateTextureFromSurface(Game::renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	return tex;
}



void TextureManager::draw(SDL_Texture * tex, SDL_Rect src, SDL_Rect dest, const int rots, const SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, rots * ROTATION, nullptr, flip);
}
