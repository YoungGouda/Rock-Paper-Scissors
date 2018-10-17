#include "stdafx.h"
#include "AssetManager.h"
#include "ECS.h"

AssetManager::AssetManager(Manager* man) : manager_(man)
{}

AssetManager::~AssetManager()
= default;

void AssetManager::add_texture(std::string id, const char * path)
{
	textures_.emplace(id, TextureManager::load_texture(path));
}

SDL_Texture * AssetManager::get_texture(const std::string id)
{
	return textures_[id];
}

void AssetManager::add_font(std::string id, std::string path, int fontSize)
{
	TTF_Font * font = TTF_OpenFont(path.c_str(), fontSize);
	if (font)
		fonts_.emplace(id, font);
	else
		std::cout << "TTF_OpenFont: " << TTF_GetError() << std::endl;
}

TTF_Font * AssetManager::get_font(std::string id)
{
	return fonts_[id];
}
