#pragma once
#include "SDL.h"

struct Animation
{
	int index;
	int frames;
	int speed;
	int rotations;
	SDL_RendererFlip flip;

	Animation()
	{

	}
	Animation(int i, int f, int s)
	{
		index = i;
		frames = f;
		speed = s;
		rotations = 0;
		flip = SDL_FLIP_NONE;
	}

	Animation(int i, int f, int s, int rots, SDL_RendererFlip flp)
	{
		index = i;
		frames = f;
		speed = s;
		rotations = rots;
		flip = flp;
	}

};