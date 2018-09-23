#pragma once
#include <SDL.h>
#undef main
#include <string>

class KeyboardHandler
{
public:

	KeyboardHandler()
	{}

	bool checkKeyEvent(SDL_Keycode key, SDL_EventType type)
	{
		return keyEvents[key] == type;
	}

	bool checkKeyState(SDL_Scancode keyCode) {
		return (keystates[keyCode]);
	}

	const Uint8* keystates = SDL_GetKeyboardState(NULL);

	Uint32 keyEvents[];
private:
};