#pragma once

#include "SDL.h"

class Collision{
public:
	static bool aabb(const SDL_Rect& rec_a, const SDL_Rect& rec_b);
};