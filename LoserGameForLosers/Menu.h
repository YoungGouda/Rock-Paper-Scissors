#pragma once
#include "GameState.h"
#include "Constants.h"
#include "Components.h" 

class Menu : public GameState
{

public:
	Menu(Manager *manager);
	~Menu()
	{}

	void render() override;
	void logic() override;
	void handle_events() override;
	void close() override;
private:
	Manager* manager_;
};
