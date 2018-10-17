
#include "stdafx.h"
#include "Combat.h"
#include <SDL.h>
#include "Constants.h"
#include "ECS.h"
#include "Character.h"
#include <limits>

BackgroundLogic * bg_logic;
EndOfRoundLogic * eor_logic;

std::vector<SDL_Scancode> keys = { SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_1, SDL_SCANCODE_2, SDL_SCANCODE_3, SDL_SCANCODE_4 };


Combat::Combat(Entity* p_left, Entity * p_right, Entity * bg) 
: player_left(p_left), player_right(p_right), background(bg)
{
	background->add_component<TransformComponent>(BACKGROUND_X_OFFSET, BACKGROUND_Y_OFFSET, BACKGROUND_HEIGHT, BACKGROUND_WIDTH, BACKGROUND_SCALING);
	background->add_component<BackgroundComponent>("background");
	background->add_group(Game::group_background);

	player_left->add_component<TransformComponent>(SPRITE_LEFT_EDGE_OF_SCREEN, SPRITE_BOTTOM_OF_SCREEN, SPRITE_LENGTH, SPRITE_LENGTH, SPRITE_SCALING);
	player_left->add_component<SpriteComponent>("arms", true);
	player_left->add_component<PlayerComponent>(true, Character(0.5f, Attack(2.0f, 0.0f, "whip"), Attack(2.75f, 2.75f, "jump kick"), Attack(0.5f, 0.5f, "grab"), "arms", 1.0));
	player_left->add_component<ControllerComponent>("debug");
	player_left->add_group(Game::group_players);

	player_right->add_component<TransformComponent>(SPRITE_RIGHT_EDGE_OF_SCREEN, SPRITE_BOTTOM_OF_SCREEN, SPRITE_LENGTH, SPRITE_LENGTH, SPRITE_SCALING);
	player_right->add_component<SpriteComponent>("square", 0, SDL_FLIP_HORIZONTAL, true);
	player_right->add_component<PlayerComponent>(false, Character(1.0f, Attack(1.5f, 0.0f, "whip"), Attack(1.5f, 1.5f, "jump kick"), Attack(1.5f, 1.5f, "grab"), "square", 0.8));
	player_right->add_component<ControllerComponent>("debug", keys);
	player_right->add_group(Game::group_players);

	player_left->get_component<PlayerComponent>().set_line_color(255, 0, 0);
	player_right->get_component<PlayerComponent>().set_line_color(0, 0, 255);

	bg_logic = new BackgroundLogic(player_left, player_right, background, 4);
	eor_logic = new EndOfRoundLogic(player_left, player_right);
}

Combat::~Combat()
{}


void Combat::handle_events()
{
	SDL_PollEvent(&Game::event);

	switch (Game::event.type)
	{
	case SDL_QUIT:
		Game::is_running = false;
		break;
	default:
		break;
	}
}

void Combat::logic()
{
	const auto player1_x = player_left->get_component<TransformComponent>().position.x;
	const auto player2_x = player_right->get_component<TransformComponent>().position.x;

	manager.refresh();
	manager.update();

	bg_logic->screen_change(player1_x, player2_x);

	/*if (!eor_logic->check_winner())
		std::cout << "Wow, a whiff" << std::endl;*/

}

auto& player_group = manager.get_group(Game::group_players);
auto& background_group = manager.get_group(Game::group_background);

void Combat::render()
{
	for (auto& b : background_group)
	{
		b->draw();
	}
	for (auto& p : player_group)
	{
		p->draw();
	}
}


