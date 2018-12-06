#pragma once
#include "SDL.h"

struct Animation
{
	int index;
	int frames;
	int speed;
	int rotations;
	SDL_RendererFlip flip;

	Animation(): index(0), frames(0), speed(0), rotations(0), flip(SDL_FLIP_NONE)
	{}

	Animation(const int i, const int f, const int s)
	{
		index = i;
		frames = f;
		speed = s;
		rotations = 0;
		flip = SDL_FLIP_NONE;
	}

	Animation(const int i, const int f, const int s, const int rots, const SDL_RendererFlip flp)
	{
		index = i;
		frames = f;
		speed = s;
		rotations = rots;
		flip = flp;
	}

};