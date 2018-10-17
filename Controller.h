#pragma once
#include <utility>
#include "ECS.h"
#include "ControllerConstants.h"
#include "ControllerCommands.h"

class Controller
{
private:
	Entity * entity_;

	Command * move_left_command_ = new MoveCommand(-1, "walk left");
	Command * move_right_command_ = new MoveCommand(1, "walk right");
	Command * idle_command_ = new MoveCommand(0, "idle");
	Command * choose_whip_command_ = new SelectAttackCommand("whip");
	Command * choose_jump_kick_command_ = new SelectAttackCommand("jump kick");
	Command * choose_grab_command_ = new SelectAttackCommand("grab");
	Command * pause_game_command_ = new PauseGameCommand();
	Command * cursor_up_command_ = new MoveCursorYCommand(-1);
	Command * cursor_down_command_ = new MoveCursorYCommand(1);
	Command * cursor_left_command_ = new MoveCursorXCommand(-1);
	Command * cursor_right_command_ = new MoveCursorXCommand(1);
	Command * cursor_select_ = new MakeSelection();
	Command * main_menu_command_ = new GoToMenuCommand();

	std::vector<Command *> commands_
	{ 
		move_left_command_,
		move_right_command_, 
		idle_command_, 
		choose_whip_command_, 
		choose_jump_kick_command_, 
		choose_grab_command_, 
		pause_game_command_,
		cursor_up_command_,
		cursor_down_command_,
		cursor_left_command_,
		cursor_right_command_,
		cursor_select_,
		main_menu_command_
	};

public:

	std::vector<std::pair<int, Command *>> current_controller;

	Controller(std::vector<Input> controller_inputs)
	{
		for (auto c : controller_inputs)
		{
			current_controller.push_back( std::pair<int, Command *>( c.keys, commands_[c.command] ) );
		}
	}

};


