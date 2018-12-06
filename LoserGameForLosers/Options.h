#pragma once
#include "SDL.h"
#include <vector>
#include "Vector2D.h"
#include "OptionLinks.h"
#include "LinkCommands.h"


class Options
{
	std::vector<Link *> links_ {new CursorLeftLink(new ChangeStateCommand(STATE_COMBAT)), new CursorLeftLink(new NothingCommand()), new CursorLeftLink(new NothingCommand()), new CursorLeftLink(new NothingCommand()), new NoAssetLink(new NothingCommand), new NoAssetLink(new NothingCommand),  new NoAssetLink(new NothingCommand), new NoAssetLink(new NothingCommand) };

public:
	Options(Choices* choices)
	{
		std::vector<Link *> y_links{};
		SDL_Rect starting_rect{};
		//sets the starting position to the first option
		
		choices->options[0][0].position = choices->link_parameters.starting_position;
		links_[choices->options[0][0].link]->set_link_information(choices->link_parameters, choices->options[0][0].position, choices->options[0][0].asset);
		
		// sets up the first rect to be used in alignment calculations
		starting_rect = links_[choices->options[0][0].link]->get_box_dimensions();

		option_rect = starting_rect;

		for (auto x = 0; x < choices->options.size(); x++)
		{
			y_links.clear();
			for (auto y = 0; y < choices->options[x].size(); y++)
			{
				auto current_link = links_[choices->options[x][y].link];
				current_link->set_link_information(choices->link_parameters, choices->options[x][y].position, choices->options[x][y].asset, &starting_rect);
				y_links.push_back(current_link);

				// setting up next x link position if it exists
				if (x+1 < choices->options.size())
					choices->options[x+1][y].position = Vector2D(current_link->get_box_dimensions().x + current_link->get_box_dimensions().w,
						current_link->get_box_dimensions().y);

				// setting up next y link position if it exists
				if (y+1 < choices->options[x].size())
					choices->options[x][y+1].position = Vector2D(current_link->get_box_dimensions().x,
						current_link->get_box_dimensions().y + current_link->get_box_dimensions().h);

				// setting up option_rect 
				if (option_rect.x > current_link->get_box_dimensions().x)
					option_rect.x = current_link->get_box_dimensions().x;
				if (option_rect.y > current_link->get_box_dimensions().y)
					option_rect.y = current_link->get_box_dimensions().y;
				if (option_rect.x + option_rect.w < current_link->get_box_dimensions().x + current_link->get_box_dimensions().w)
					option_rect.w += current_link->get_box_dimensions().x + current_link->get_box_dimensions().w - (option_rect.x + option_rect.w);
				if (option_rect.y + option_rect.h < current_link->get_box_dimensions().y + current_link->get_box_dimensions().h)
					option_rect.h += current_link->get_box_dimensions().y + current_link->get_box_dimensions().h - (option_rect.y + option_rect.h);
				
				std::cout << "cursor dimensions = ( " << current_link->get_cursor_dimensions().x << ", " << current_link->get_cursor_dimensions().y << ", " << current_link->get_cursor_dimensions().w << ", " << current_link->get_cursor_dimensions().h << " )" << std::endl;
				std::cout << "box dimensions = ( " << current_link->get_box_dimensions().x << ", " << current_link->get_box_dimensions().y << ", " << current_link->get_box_dimensions().w << ", " << current_link->get_box_dimensions().h << " )" << std::endl;
				std::cout << "link dimensions = ( " << current_link->get_link_dimensions().x << ", " << current_link->get_link_dimensions().y << ", " << current_link->get_link_dimensions().w << ", " << current_link->get_link_dimensions().h << " )" << std::endl;

			}
			option_links.push_back(y_links);
		}
		std::cout << "option dimensions = ( " << option_rect.x << ", " << option_rect.y << ", " << option_rect.w << ", " << option_rect.h << " )" << std::endl;
	}

	std::vector<std::vector<Link *>> option_links{};
	SDL_Rect option_rect{};
};
