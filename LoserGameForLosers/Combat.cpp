
#include "stdafx.h"
#include "Combat.h"

Background * bg_logic;

CombatProcessor *processor = nullptr;

std::vector<SDL_Scancode> keys = { SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_I, SDL_SCANCODE_O, SDL_SCANCODE_P, SDL_SCANCODE_L };

Combat::Combat(Manager * manager)
	: manager_(manager)
{
	auto& background(manager_->add_entity());
	auto& player_left(manager_->add_entity());
	auto& player_right(manager_->add_entity());

	background.add_component<TransformComponent>(BACKGROUND_X_OFFSET, BACKGROUND_Y_OFFSET, BACKGROUND_HEIGHT, BACKGROUND_WIDTH, BACKGROUND_SCALING);
	background.add_component<TextureComponent>("background");
	background.add_component<BackgroundComponent>();
	background.add_group(Game::group_background);

	player_left.add_component<TransformComponent>(SPRITE_LEFT_EDGE_OF_SCREEN, SPRITE_BOTTOM_OF_SCREEN, SPRITE_LENGTH, SPRITE_LENGTH, SPRITE_SCALING);
	player_left.add_component<TextureComponent>("player left");
	player_left.add_component<PlayerComponent>(true, Game::game_settings->player1);
	player_left.add_component<SpriteComponent>(true);
	player_left.add_component<ControllerComponent>("debug");
	player_left.add_component<ColliderComponent>();
	player_left.add_group(Game::group_players);

	player_right.add_component<TransformComponent>(SPRITE_RIGHT_EDGE_OF_SCREEN, SPRITE_BOTTOM_OF_SCREEN, SPRITE_LENGTH, SPRITE_LENGTH, SPRITE_SCALING);
	player_right.add_component<TextureComponent>("player right");
	player_right.add_component<PlayerComponent>(false, Game::game_settings->player2);
	player_right.add_component<SpriteComponent>(0, SDL_FLIP_HORIZONTAL, true);
	player_right.add_component<ControllerComponent>("debug", keys);
	player_right.add_component<ColliderComponent>();
	player_right.add_group(Game::group_players);

	bg_logic = new Background(&player_left, &player_right, &background, PLAYER_MAX_RANGE);
	/*processor = new CombatProcessor(&player_left, &player_right, &background);

	processor->create_combat();*/
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
	bg_logic->screen_change();

	manager.refresh();
	manager.update();

	/*if (processor->tasks[processor->current_task]->do_work())
		processor->next_process();*/
}



void Combat::render()
{
	
}

void Combat::close()
{
	for (auto& b : manager_->get_group(Game::group_background))
	{
		b->del_group(Game::group_background);
		b->destroy();
	}

	for (auto& p : manager_->get_group(Game::group_players))
	{
		p->del_group(Game::group_players);
		p->destroy();
	}

	for (auto& pr : manager_->get_group(Game::group_prompts))
	{
		pr->del_group(Game::group_prompts);
		pr->destroy();
	}
}




