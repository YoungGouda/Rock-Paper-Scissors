#pragma once

#include <string>
#include "ECS.h"
#include <SDL.h>
#include <cmath>

extern Manager manager;

class ControllerComponent : public Component
{
private:
	int frameCount = 0;
	float vScale;
public:

	KeyboardHandler * keyboard = new KeyboardHandler();
	SDL_Scancode keys[3] = { SDL_SCANCODE_RIGHT, SDL_SCANCODE_LEFT, SDL_SCANCODE_P };

	ControllerComponent(float vSc) : vScale(vSc)
	{}
	ControllerComponent(float vSc, SDL_Scancode k[3]) : vScale(vSc)
	{
		for (int i = 0; i < 2; i++)
		{
			keys[i] = k[i];
		}

	}

	~ControllerComponent()
	{}

	void setVelocityScale(float newVelocity)
	{
		vScale = newVelocity;
	}

	float getVelocityScale()
	{
		return vScale;
	}
	
	void createPlayerMovement()
	{
		TransformComponent* playerTC = &entity->getComponent<TransformComponent>();
		SpriteComponent* playerSC = &entity->getComponent<SpriteComponent>();

		if (!keyboard->checkKeyState(keys[0]) && !keyboard->checkKeyState(keys[1]))
		{
			playerSC->Play("idle");
			playerTC->velocity.x = 0;
		}
		if (keyboard->checkKeyState(keys[0]))
		{
			playerSC->Play("walkRight");
			if (playerTC->scale >= SPRITE_SCALING)
				playerTC->velocity.x = vScale;
			
		}
		else if (keyboard->checkKeyState(keys[1]))
		{
			playerSC->Play("walkLeft");
			if (playerTC->scale >= SPRITE_SCALING)
				playerTC->velocity.x = -vScale;
		}
	}
	void createPlayerActions()
	{
		if (keyboard->checkKeyState(keys[2]))
			Game::endOfRound = !Game::endOfRound;
	}

	

	void update() override
	{
		if (frameCount % 5 == 0)
		{
			createPlayerMovement();
			createPlayerActions();
		}
		frameCount++;
	}

};

