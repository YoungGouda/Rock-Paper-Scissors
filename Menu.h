#pragma once
#include "GameState.h"

class Menu : public GameState
{
public:
	Menu(Entity * cursor, Entity * screen);
	~Menu()
	{
		std::cout << "I am destroying" << std::endl;
		cursor_->destroy();
		screen_->destroy();
	}

	void render() override;
	void logic() override;
	void handle_events() override;

private:
	Entity * cursor_, *screen_;

};
