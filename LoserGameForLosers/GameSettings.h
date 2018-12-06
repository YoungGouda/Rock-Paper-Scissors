#pragma once
#include "Character.h"
#include "SDL.h"

class GameSettings
{
public:
	Character player1 = Character();
	Character player2 = Character();
	const char * background_path = "western industrial.jpg";

	GameSettings()
	{}
};