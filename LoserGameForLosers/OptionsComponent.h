#pragma once
#include "ECS.h"
#include <map>
#include "Options.h"

class OptionsComponent: public Component
{
	const char * screen_id_;

	Choices* option_choices_;

	int y_pos_;
	int x_pos_;
	
public:
	Options * current_options{};

	OptionsComponent()
		:screen_id_("main")
	{}

	explicit OptionsComponent(Choices* choices)
		: option_choices_(choices)
	{}

	void init() override
	{
		y_pos_ = 0;
		x_pos_ = 0;
		current_options = new Options(option_choices_);
	}

	void load_new_options(Choices* choices)
	 {
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