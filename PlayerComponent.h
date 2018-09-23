#pragma once
#include "ECS.h"
#include <map>
#include "Attack.h"

extern Manager manager;

class PlayerComponent : public Component
{
public:
	std::map<const char *, Attack> attacks;
	int numWins;
	bool PriorityPlayer;
	Attack chosenAttack;
	std::string playerName;
	Uint8 red = 0;
	Uint8 green = 0;
	Uint8 blue = 0;


	PlayerComponent() 
	{
		playerName = "NOT GOOD";
		PriorityPlayer = false;
		numWins = 0;

	}

	PlayerComponent(bool hasPriority, std::string name) : PriorityPlayer(hasPriority)
	{
		playerName = name;

		numWins = 0;

		Attack whip(WHIP_RANGE, WHIP_WHIF, "whip");
		Attack jumpKick(JUMP_KICK_RANGE, JUMP_KICK_WHIF, "jump kick");
		Attack grab(GRAB_RANGE, GRAB_WHIF, "grab");

		attacks.emplace("whip", whip);
		attacks.emplace("jump kick", jumpKick);
		attacks.emplace("grab", grab);
	}

	~PlayerComponent()
	{}

	void switchPriority()
	{
		ControllerComponent * playerCC = &entity->getComponent<ControllerComponent>();

		PriorityPlayer = !PriorityPlayer;
		if (PriorityPlayer)
			playerCC->setVelocityScale(PLAYER_VELOCITY);
		else
			playerCC->setVelocityScale(PLAYER_PRIORITY_VELOCITY);
	}

	void roundWin()
	{
		numWins++;
	}

	void chooseAttack(const char * attID)
	{
		chosenAttack = attacks[attID];
	}

	void setLineColor(Uint8 r, Uint8 g, Uint8 b)
	{
		red = r;
		green = g;
		blue = b;
	}

	void draw() override
	{
		Vector2D position = entity->getComponent<TransformComponent>().position;
		int scaledSize = entity->getComponent<TransformComponent>().scale * SPRITE_LENGTH;
		int direction = 1;

		if (entity->getComponent<SpriteComponent>().spriteflip == SDL_FLIP_HORIZONTAL)
			direction = -1;

		
		SDL_SetRenderDrawColor(Game::renderer, red, green, blue, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(Game::renderer, position.x + scaledSize / 2, position.y + scaledSize / 2 + direction * 3, position.x + chosenAttack.Range * scaledSize * direction + scaledSize / 2, position.y + scaledSize / 2 + direction * 3);
		SDL_SetRenderDrawColor(Game::renderer, red, red, red, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(Game::renderer, position.x + scaledSize / 2, position.y + scaledSize / 3 + direction * 3, position.x + chosenAttack.whifDistance * scaledSize * direction + scaledSize / 2, position.y + scaledSize / 3 + direction * 3);
		if (PriorityPlayer)
		{
			SDL_SetRenderDrawColor(Game::renderer, blue, blue, blue, SDL_ALPHA_OPAQUE);
			SDL_RenderDrawLine(Game::renderer, position.x + scaledSize / 2, position.y + scaledSize, position.x + scaledSize / 2, position.y);

		}
	}
};
