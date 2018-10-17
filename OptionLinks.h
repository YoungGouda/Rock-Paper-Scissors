#pragma once
#include "Game.h"
#include "GameState.h"
#include "OptionsConstants.h"


class Link
{
public:
	virtual ~Link() {}
	virtual void set_link_information(LinkBuilder link_information, Vector2D pos, const char * asset, SDL_Rect starting_rect) = 0;

	virtual std::string get_text() = 0;
	virtual std::string get_font() = 0;
	virtual SDL_Rect get_link_dimensions() = 0;
	virtual SDL_Rect get_box_dimensions() = 0;
	virtual SDL_Rect get_cursor_dimensions() = 0;
	virtual Command * get_command() = 0;
};



class CursorLeftLink : public Link
{
public:
	explicit CursorLeftLink(Command * command)
		: command_(command), previous_state_(0)
	{}

	~CursorLeftLink()
	{}

	void set_link_information(const LinkBuilder link_information, const Vector2D pos, const char * asset, SDL_Rect starting_rect) override
	{
		font_ = link_information.font;
		text_ = asset;

		int w, h;

		TTF_SizeText(Game::assets->get_font(font_), text_.c_str(), &w, &h);

		if (h < CURSOR_HEIGHT)
			h = CURSOR_HEIGHT;

		link_dimensions_ = SDL_Rect{ static_cast<int>(pos.x) + CURSOR_WIDTH + 4 * link_information.padding, static_cast<int>(pos.y) + 2 * link_information.padding, w + 2 * link_information.padding, h + 2 * link_information.padding };
		cursor_dimensions_ = SDL_Rect{ static_cast<int>(pos.x) + 2 * link_information.padding, static_cast<int>(pos.y) + 2 * link_information.padding, CURSOR_WIDTH, CURSOR_WIDTH };
		box_dimensions_ = SDL_Rect{ static_cast<int>(pos.x), static_cast<int>(pos.y), link_dimensions_.w + cursor_dimensions_.w + link_information.padding * 6, link_dimensions_.h + link_information.padding * 4};
	}

	std::string get_text() override { return text_; }
	std::string get_font() override { return font_; }
	SDL_Rect get_link_dimensions() override { return link_dimensions_; }
	SDL_Rect get_box_dimensions() override { return box_dimensions_; }
	SDL_Rect get_cursor_dimensions() override { return cursor_dimensions_; }
	Command* get_command() override { return command_; }
	
	
private:
	Command * command_;
	int previous_state_;
	std::string text_, font_;
	SDL_Rect link_dimensions_{};
	SDL_Rect box_dimensions_{};
	SDL_Rect cursor_dimensions_{};
};
