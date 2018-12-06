#pragma once
#include "Components.h"
#include "Vector2D.h"
#include "Game.h"

class TransformComponent : public Component
{
public:
	Vector2D position;
	Vector2D net_velocity, player_velocity, external_velocity;

	int height = 32;
	int width = 32;
	float scale = 1.0;


	int speed = 3;

	TransformComponent()
	{
		position.x = 0.0f;
		position.y = 0.0f;
	}

	explicit TransformComponent(int sc)
		: scale(sc)
	{
		position.x = 400;
		position.y = 320;
	}

	TransformComponent(const float x, const float y)
	{
		position.x = x;
		position.y = y;
	}

	TransformComponent(const float x, const float y, const int h, const int w, const float sc)
		: height(h), width(w), scale(sc)
	{
		position.x = x;
		position.y = y;
	}

	void init() override
	{
		net_velocity.x = 0;
		net_velocity.y = 0;
		external_velocity.x = 0;
		external_velocity.y = 0;

		net_velocity = player_velocity + external_velocity;
	}

	void update() override
	{
		position.x += net_velocity.x * static_cast<float>(speed);
		position.y += net_velocity.y * speed;
	}
};