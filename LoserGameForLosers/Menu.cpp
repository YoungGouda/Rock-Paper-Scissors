#include "stdafx.h"
#include "Menu.h"

Menu::Menu(Manager * manager)
	: manager_(manager)
{
	auto& screen(manager_->add_entity());

	screen.add_component<TransformComponent>(BACKGROUND_X_OFFSET, BACKGROUND_Y_OFFSET, BACKGROUND_HEIGHT, BACKGROUND_WIDTH, BACKGROUND_SCALING_TARGET);
	screen.add_component<TextureComponent>("main");
	screen.add_component<MenuComponent>();
	screen.add_group(Game::group_background);

	Game::assets->create_option_box(Choices
	({ { Option(0, "Play Game"), Option(1, "Option 2"), Option(2, "Option 3"), Option(3, "Option 4") } },
		LinkBuilder(5, Vector2D(1, 0), Vector2D(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 64), "lazy")
	), true, { "box", "cursor", "bitmap" });
}


void Menu::render()
{
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

void Menu::close()
{
	for (auto& b : manager_->get_group(Game::group_background))
	{
		b->del_group(Game::group_background);
		b->destroy();
	}

	for (auto& c : manager_->get_group(Game::group_cursors))
	{
		c->del_group(Game::group_cursors);
		c->destroy();
	}
}
