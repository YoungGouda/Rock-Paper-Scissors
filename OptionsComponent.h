#pragma once
#include "ECS.h"
#include <map>
#include "Options.h"

class OptionsComponent: public Component
{
	Choices main_screen_ =
		Choices
		({ { Option(0), Option(1), Option(2), Option(3)} },
				LinkBuilder(5, Vector2D(0.5, 0), Vector2D(SCREEN_WIDTH / 8, SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 8), "gil sans")
			);

	const char * screen_id_;

	std::map<const char *, Choices> screen_map_;

	int y_pos_;
	int x_pos_;
	
public:
	Options * current_options{};

	OptionsComponent()
		:screen_id_("main")
	{}

	explicit OptionsComponent(const char * screen_id)
		: screen_id_(screen_id)
	{}

	void init() override
	{
		y_pos_ = 0;
		x_pos_ = 0;
		screen_map_.emplace("main", main_screen_);
		current_options = new Options(screen_map_[screen_id_]);
	}

	void change_screen(const char * new_screen)
	 {
		current_options = new Options(screen_map_[new_screen]);
	 }

	void load_options(const Choices& choices, const char * screen_id)
	 {
		screen_map_.emplace(screen_id, choices);
		current_options = new Options(choices);
	 }

	void next_x(const int x_inc)
	{
		x_pos_ += x_inc;
		if (x_pos_ < 0)
			x_pos_ = current_options->option_links.size() - 1;
		if (x_pos_ > current_options->option_links.size() - 1)
			x_pos_ = 0;
	}

	void next_y(const int y_inc)
	{
		y_pos_ += y_inc;
		if (y_pos_ < 0)
			y_pos_ = current_options->option_links[x_pos_].size() - 1;
		if (y_pos_ > current_options->option_links[x_pos_].size() - 1)
			y_pos_ = 0;
	}

	Link * get_current_link() const
	{
		return current_options->option_links[x_pos_][y_pos_];
	}
	
};