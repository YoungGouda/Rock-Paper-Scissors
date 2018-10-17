#pragma once

#include "ECS.h"
#include <SDL.h>
#include "Controller.h"

class ControllerComponent : public Component
{
	KeyboardHandler * keyboard_;

	std::vector<SDL_Scancode> keys_ = {SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_I, SDL_SCANCODE_O, SDL_SCANCODE_P, SDL_SCANCODE_L};

	std::vector<Input> debug_controller_ = {Input(0,2), Input(1,3), Input(2,-23), Input(3, 4), Input(4, 5), Input(5, 6), Input(12, 7)};
	std::vector<Input> combat_controller_ = { Input(0,2), Input(1,3), Input(2,-23), Input(6,7) };
	std::vector<Input> choose_controller_ = { Input(3, 4), Input(4, 5), Input(5, 6) };
	std::vector<Input> pause_controller_ = { Input(7, 0), Input(8, 1), Input(9, 2), Input(10, 3), Input(11, 4), Input(6,7)};
	std::vector<Input> options_controller_ = {Input(7, 0), Input(8, 1), Input(9, 2), Input(10, 3), Input(11, 4)};

	std::map<std::string, std::vector<Input>> input_controller_;

	std::string controller_id_;

	Controller * command_controller_;
public:


	ControllerComponent(const std::string controller_id) : controller_id_(controller_id)
	{}
	ControllerComponent(const std::string controller_id, const std::vector<SDL_Scancode> keys) : keys_(keys), controller_id_(controller_id)
	{}

	~ControllerComponent()
	= default;

	void init() override
	{
		input_controller_.emplace("debug", debug_controller_);
		input_controller_.emplace("combat", combat_controller_);
		input_controller_.emplace("select attack", choose_controller_);
		input_controller_.emplace("pause", pause_controller_);
		input_controller_.emplace("options", options_controller_);

		keyboard_ = new KeyboardHandler;
		command_controller_ = new Controller(input_controller_[controller_id_]);
	}

	void change_controller(const std::string new_controller)
	{
		command_controller_ = new Controller(input_controller_[new_controller]);
	}

	void reset_controller()
	{
		command_controller_ = new Controller(input_controller_[controller_id_]);
	}

	bool input_check(const int key)
	{
		auto is_pressed = true;

		const auto first_key = key % 10;

		if (first_key < 0)
			is_pressed *= !keyboard_->check_key_state(keys_[std::abs(first_key)]);		
		else
			is_pressed *= keyboard_->check_key_state(keys_[first_key]);
		if (std::abs(key) > 9)
			is_pressed *= input_check(key / 10);

		return is_pressed;
	}

	void update() override
	{
		for (auto& c : command_controller_->current_controller)
		{
			if (input_check(c.first))
				c.second->execute(entity);
		}
	}

};

