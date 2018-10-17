#include "stdafx.h"
#include "Menu.h"
#include "Combat.h"
#include "GameState.h"


Manager manager;

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;

KeyboardHandler* key_handler = new KeyboardHandler();
AssetManager* Game::assets = new AssetManager(&manager);
GameState * current_state = nullptr;

bool Game::is_running = false;

auto& player_1(manager.add_entity());
auto& player_2(manager.add_entity());
auto& background(manager.add_entity());
auto& cursor(manager.add_entity());
auto& screen(manager.add_entity());

//State variables

int Game::state_id = STATE_NULL;
int next_state = STATE_NULL;


void Game::init(const char * window_title)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}
		if (TTF_Init() == -1) {
			printf("TTF_Init: %s\n", TTF_GetError());
			exit(2);
		}
		Game::is_running = true;
	}

	assets->add_texture("player", "Fighter_full.png");
	assets->add_texture("background", "western industrial.jpg");
	assets->add_texture("square", "square_full.png");
	assets->add_texture("arms", "LongArms_full.png");
	assets->add_texture("box", "textbox.png");
	assets->add_texture("cursor", "cursor.png");
	assets->add_texture("main", "Title_screen.png");

	assets->add_font("gil sans", "GIL_____.TTF", 18);

	current_state = new Menu(&cursor, &screen);
	state_id = STATE_MENU;
	
}

// Stolen verbatim from @LazyFooProductions
void Game::set_next_state(const int new_state)
{
	//If the user doesn't want to exit
	if (next_state != STATE_EXIT)
	{
		//Set the next state
		next_state = new_state;
	}
}

// Stolen verbatim from @LazyFooProductions
void change_state()
{
	//If the state needs to be changed
	if (next_state != STATE_NULL)
	{
		//Delete the current state
		if (next_state != STATE_EXIT)
		{
			current_state = nullptr;
		}

		//Change the state
		switch (next_state)
		{
		case STATE_MENU:
			current_state = new Menu(&cursor, &screen);
			break;

		case STATE_COMBAT:
			current_state = new Combat(&player_1, &player_2, &background);
			break;
		default: ;
		}

		//Change the current state ID
		Game::state_id = next_state;

		//NULL the next state ID
		next_state = STATE_NULL;
	}
}

void Game::update()
{
	change_state();
	current_state->logic();
}

void Game::render()
{
	SDL_RenderClear(renderer);
	current_state->render();
	SDL_RenderPresent(renderer);
}

void Game::handle_events()
{
	current_state->handle_events();
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

