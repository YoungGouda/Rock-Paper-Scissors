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

	explicit TransformComponent(const int sc)
	{
		position.x = 400;
		position.y = 320;
		scale = sc;
	}

	TransformComponent(const float x, const float y)
	{
		position.x = x;
		position.y = y;
	}

	TransformComponent(const float x, const float y, const int h, const int w, const float sc)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	void set_x_velocity(const int x)
	{
		velocity.x = x;
	}

	void set_x_position(const float x)
	{
		position.x = x;
	}

	void set_x_position_and_scaling(const float x, const float sc)
	{
		position.x = x;
		scale = sc;
	}

	void set_y_position(const int y)
	{
		position.y = y;
	}

	void set_scaling(const float sc)
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
		position.x += velocity.x * static_cast<float>(speed);
		position.y += velocity.y * speed;
	}
};