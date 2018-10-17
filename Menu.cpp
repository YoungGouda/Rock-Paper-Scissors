#include "stdafx.h"
#include "Menu.h"
#include "Constants.h"

extern Manager manager;

Menu::Menu(Entity * cursor, Entity * screen)
	: cursor_(cursor), screen_(screen)
{
	SDL_Color black = { 0, 0, 0, 255 };

	screen_->add_component<TransformComponent>(BACKGROUND_X_OFFSET, BACKGROUND_Y_OFFSET, BACKGROUND_HEIGHT, BACKGROUND_WIDTH, BACKGROUND_SCALING_TARGET);
	screen_->add_component<MenuComponent>("main");
	screen_->add_group(Game::group_screens);

	cursor_->add_component<OptionsComponent>("main");
	cursor_->add_component<BoxComponent>(1, "box");
	cursor_->add_component<TTFComponent>(black);
	cursor_->add_component<CursorComponent>("cursor", 0, SDL_FLIP_NONE);
	cursor_->add_component<ControllerComponent>("options");
	cursor_->add_group(Game::group_cursors);
}

auto& cursor_group = manager.get_group(Game::group_cursors);
auto& screen_group = manager.get_group(Game::group_screens);

void Menu::render()
{
	for (auto& c : screen_group)
	{
		c->draw();
	}
	for (auto& c : cursor_group)
	{
		c->draw();
	}
}

void Menu::logic()
{
	manager.refresh();
	manager.update();
}

void Menu::handle_events()
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
