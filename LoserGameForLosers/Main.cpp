// LoserGameForLosers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"
#include "Constants.h"

Game* game = nullptr;

int main()
{
	game = new Game();
	game->init("Rock Paper Scissors");
	while (game->running())
	{
		const auto frame_start = SDL_GetTicks();

		game->handle_events();
		game->update();
		game->render();

		const int frame_time = SDL_GetTicks() - frame_start;

		if (FRAME_DELAY > frame_time)
		{
			SDL_Delay(FRAME_DELAY - frame_time);
		}
	}

	game->clean();

    return 0;
}

