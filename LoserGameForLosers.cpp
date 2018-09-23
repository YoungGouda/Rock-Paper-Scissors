// LoserGameForLosers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"
#include "Constants.h"

Game* game = nullptr;

int main()
{
	Uint32 frameStart;
	int frameTime;

	game = new Game();
	game->init("Rock Paper Scissors");

	while (game->running())
	{

		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (FRAME_DELAY > frameTime)
		{
			SDL_Delay(FRAME_DELAY - frameTime);
		}
	}

	game->clean();

    return 0;
}

