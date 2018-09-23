#pragma once
#include "Components.h"
#include "Vector2D.h"

class TransformComponent : public Component
{

public:

	Vector2D position;
	Vector2D velocity;

	int height = 32;
	int width = 32;
	float scale = 1.0;

	int speed = 3;

	TransformComponent()
	{
		position.x = 0.0f;
		position.y = 0.0f;
	}

	TransformComponent(int sc)
	{
		position.x = 400;
		position.y = 320;
		scale = sc;
	}

	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y, int h, int w, float sc)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	void setXVelocity(int x)
	{
		velocity.x = x;
	}

	void setXPosition(float x)
	{
		position.x = x;
	}

	void setXPositionAndScaling(float x, float sc)
	{
		position.x = x;
		scale = sc;
	}

	void setYPosition(int y)
	{
		position.y = y;
	}

	void setScaling(float sc)
	{
		scale = sc;
	}

	void init() override
	{
		velocity.x = 0;
		velocity.y = 0;
	}
	void update() override
	{
		position.x += velocity.x * (float)speed;
		position.y += velocity.y * speed;
	}
};