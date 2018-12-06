#pragma once
#include "ECS.h"
#include "Components.h"


class ColliderComponent : public Component
{
private:
	bool flipped_;
	Uint8 red_, green_, blue_;
public:

	SDL_Rect collider{};
	std::string tag;
	bool draw_attack;

	SDL_Rect src_r, dest_r;

	TransformComponent* transform;

	float hit_box = 1.0;
	int projectile_point;

	ColliderComponent() {}

	ColliderComponent(const std::string& t)
	{
		tag = t;
	}

	ColliderComponent(const std::string& t, const int x, const int y, const int size)
	{
		tag = t;
		collider.x = x;
		collider.y = y;
		collider.h = collider.w = size;
	}

	void init() override
	{
		transform = &entity->get_component<TransformComponent>();
		flipped_ = false;
		draw_attack = false;

		red_ = 0;
		green_ = 0;
		blue_ = 0;

		if (entity->has_component<SpriteComponent>())
			if (entity->get_component<SpriteComponent>().sprite_flip == SDL_FLIP_HORIZONTAL)
				flipped_ = true;

		if (entity->has_component<PlayerComponent>())
		{
			tag = entity->get_component<PlayerComponent>().player_name;
			hit_box = entity->get_component<PlayerComponent>().player_identity.hit_box;
		}
	}

	void draw_attack_collider()
	{
		auto transform = entity->get_component<TransformComponent>();
		auto player = entity->get_component<PlayerComponent>();

		SDL_SetRenderDrawColor(Game::renderer, red_, green_, blue_, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(Game::renderer, projectile_point, collider.y + 10,
			projectile_point + player.chosen_attack->projectile_range * transform.scale * transform.height * player.direction, collider.y + 10);
	}

	void draw_collision()
	{
		SDL_SetRenderDrawColor(Game::renderer, red_, green_, blue_, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(Game::renderer, new SDL_Rect{ projectile_point, collider.y, static_cast<int>(entity->get_component<PlayerComponent>().chosen_attack->projectile_range * transform->scale * transform->height) * entity->get_component<PlayerComponent>().direction, static_cast<int>(transform->scale * transform->height) });
	}

	void draw_movement()
	{
		SDL_SetRenderDrawColor(Game::renderer, red_, green_, blue_, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(Game::renderer, new SDL_Rect{ projectile_point, collider.y, static_cast<int>(entity->get_component<PlayerComponent>().chosen_attack->move_distance * transform->scale * transform->height) * entity->get_component<PlayerComponent>().direction, static_cast<int>(transform->scale * transform->height) });
	}

	void set_color(Uint8 r, Uint8 g, Uint8 b)
	{
		red_ = r;
		green_ = g;
		blue_ = b;
	}

	void update() override
	{
		collider.x = static_cast<int>(transform->position.x);
		projectile_point = transform->position.x + transform->width * transform->scale * (1 - hit_box);
		if (flipped_)
		{
			collider.x = transform->position.x + transform->width * transform->scale * (1 - hit_box);
			projectile_point = transform->position.x + transform->width * transform->scale * (1 - hit_box);
		}
		collider.y = static_cast<int>(transform->position.y);
		collider.w = transform->width * transform->scale * hit_box;
		collider.h = transform->height * transform->scale;

	}

	void draw() override
	{
		if (draw_attack)
		{
			draw_collision();
		}
	}

};