#pragma once

#include <map>
#include <string>
#include "TextureManager.h"
#include "ECS.h"
#include "SDL_ttf.h"
#include "BitMapFont.h"
#include "SDL_mixer.h"
#include "OptionsConstants.h"
#include "Vector2D.h"
#include "ECS.h"
#include "Components.h"
#include "BitmapTexture.h"

class AssetManager
{
public:
	explicit AssetManager(Manager* man);
	~AssetManager();

	void create_option_box(Choices choices, bool is_boxed, std::vector<std::string> textures);

	void create_prompt(SDL_Rect* dest, int sc, const char * texture);
	void create_prompt(SDL_Rect* dest, SDL_Rect* src, int sc, const char * texture);


	//Textures
	void add_texture(std::string id, const char* path);
	SDL_Texture * get_texture(std::string id);

	//TTF fonts
	void add_font(std::string id, std::string path, int font_size);
	TTF_Font* get_font(std::string id);
	
	//BitMap fonts
	void set_bit_map_font(std::string path);
	BitmapFont* get_bitmap_font();

	//Music
	void add_music(std::string id, const char* path);
	Mix_Music* get_music(std::string id);

	//Sounds
	void add_sound(std::string id, const char* path);
	Mix_Chunk* get_sound(std::string id);

private:
	Manager * manager_;
	BitmapFont bitmap_font_;
	BitmapTexture bitmap_tex_;
	std::map<std::string, SDL_Texture*> textures_{};
	std::map<std::string, TTF_Font*> fonts_{};
	std::map<std::string, Mix_Music*> music_{};
	std::map<std::string, Mix_Chunk*> sounds_{};
	std::vector<Choices*> choices;
};
