#pragma once
#include <SDL.h>
#undef main

class KeyboardHandler
{
public:

	KeyboardHandler(): key_events{}
	{}

	bool check_key_state(const SDL_Scancode key_code) const
	{
		return key_states[key_code];
	}

	const Uint8* key_states = SDL_GetKeyboardState(nullptr);

	Uint32 key_events[];
private:
};