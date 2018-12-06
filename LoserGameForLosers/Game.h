#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>

#include "AssetManager.h"
#include "GameSettings.h"

class Game
{
public:
	void init(const char * window_title);
	static void update();
	static void render();
	static void handle_events();
	static void set_next_state(int new_state);
	void clean();
	static bool running() { return is_running; }

	static bool is_running;
	static int state_id;
	static SDL_Renderer *renderer;
	static SDL_Event event;
	static AssetManager* assets;
	static GameSettings* game_settings;
	SDL_Window *window;

	enum group_labels : std::size_t
	{
		group_characters,
		group_background,
		group_prompts,
		group_screens,
		group_players,
		group_cursors
	};

private:
};
