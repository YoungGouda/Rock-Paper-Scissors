#pragma once


class GameState
{
public:
	virtual void logic() = 0;
	virtual void render() = 0;
	virtual void handle_events() = 0;
	virtual ~GameState() {}
};

enum game_states
{
	STATE_NULL,
	STATE_MENU,
	STATE_VIDEO,
	STATE_OVERWORLD,
	STATE_COMBAT,
	STATE_EXIT
};
