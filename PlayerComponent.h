#pragma once
#include "ECS.h"
#include <map>
#include "Attack.h"
#include "character.h"

extern Manager manager;

class PlayerComponent : public Component
{
	float hit_box_;
public:
	int num_wins;
	bool priority_player;
	Attack chosen_attack;
	std::string player_name;
	Character player_identity;

	//Debug
	Uint8 red = 0;
	Uint8 green = 0;
	Uint8 blue = 0;


	PlayerComponent() 
	{
		player_name = "NOT GOOD";
		priority_player = false;
		num_wins = 0;

	}

	PlayerComponent(const bool has_priority, const Character character) : priority_player(has_priority)
	{
		player_identity = character;
		player_name = character.id;

		num_wins = 0;
	}

	~PlayerComponent()
	{}

	void round_win()
	{
		num_wins++;
	}

	float get_velocity()
	{
		auto velocity = player_identity.velocity;
		if (priority_player)
			velocity = player_identity.velocity + PLAYER_PRIORITY_INCREMENT;
		return velocity;
	}	

	void choose_attack(const char * att_id)
	{
		chosen_attack = player_identity.attacks[att_id];
	}

	void set_line_color(const Uint8 r, const Uint8 g, const Uint8 b)
	{
		red = r;
		green = g;
		blue = b;
	}

	int get_player_distance() const
	{
		const auto player_sprite = entity->get_component<SpriteComponent>();
		const auto player_transform = entity->get_component<TransformComponent>();

		const auto scaled_size = player_transform.scale * SPRITE_LENGTH;
		const auto hit_box_size = scaled_size * player_identity.hit_box;

		int player_distance = player_transform.position.x + hit_box_size;
		
		if (player_sprite.sprite_flip == SDL_FLIP_HORIZONTAL)
			player_distance = player_transform.position.x + scaled_size - hit_box_size;

		return player_distance;
	}

	void draw() override
	{
		const auto position = entity->get_component<TransformComponent>().position;
		const int scaled_size = entity->get_component<TransformComponent>().scale * SPRITE_LENGTH;
		auto direction = 1;

		if (entity->get_component<SpriteComponent>().sprite_flip == SDL_FLIP_HORIZONTAL)
			direction = -1;

		SDL_SetRenderDrawColor(Game::renderer, red, green, blue, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(Game::renderer, get_player_distance(), position.y + scaled_size / 2 + direction * 3, get_player_distance() + chosen_attack.range * direction * scaled_size, position.y + scaled_size / 2 + direction * 3);
		SDL_SetRenderDrawColor(Game::renderer, red, red, red, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(Game::renderer, get_player_distance(), position.y + scaled_size / 3 + direction * 3, get_player_distance() + chosen_attack.whiff_distance * direction * scaled_size, position.y + scaled_size / 3 + direction * 3);
		if (priority_player)
		{
			SDL_SetRenderDrawColor(Game::renderer, blue, blue, blue, SDL_ALPHA_OPAQUE);
			SDL_RenderDrawLine(Game::renderer, get_player_distance(), position.y + scaled_size, get_player_distance(), position.y);

		}
	}
};
