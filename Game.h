#pragma once

#include <SDL.h>
#include "Constants.h"
#include <SDL_image.h>
#include "AssetManager.h"
#include "KeyboardHandler.h"


class Game
{
public:
	void init(const char * windowTitle);
	void update();
	void render();
	void handleEvents();
	void clean();
	bool running() { return isRunning; }

	static bool isRunning;
	static SDL_Renderer *renderer;
	static SDL_Event event;
	static AssetManager* assets;
	SDL_Window *window;
	static bool endOfRound;

	enum groupLabels : std::size_t
	{
		groupBackground,
		groupPlayers,
		groupColliders,
	};

private:
};