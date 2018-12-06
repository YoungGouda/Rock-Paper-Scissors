#pragma once
#include "Game.h"
#include "OptionsConstants.h"


class Link
{
public:
	virtual ~Link() {}
	virtual void set_link_information(LinkBuilder link_information, Vector2D pos, std::string asset = "", SDL_Rect * starting_rect = nullptr) = 0;

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

	void set_link_information(const LinkBuilder link_information, const Vector2D pos, const std::string asset = "", SDL_Rect * starting_rect = nullptr) override
	{
		font_ = link_information.font;
		text_ = asset;

		auto bitmap_font = Game::assets->get_bitmap_font();
		
		link_dimensions_ = bitmap_font->text_dimensions(static_cast<int>(pos.x) + CURSOR_WIDTH + 4 * link_information.padding, static_cast<int>(pos.y) + 2 * link_information.padding, asset);

		if (link_dimensions_.h < CURSOR_HEIGHT)
			link_dimensions_.h = CURSOR_HEIGHT;

		int x_offset = 0;
		int y_offset = 0;

		if (starting_rect)
		{
			x_offset = (link_dimensions_.w + CURSOR_WIDTH + link_information.padding * 6 + pos.x - (starting_rect->w + starting_rect->x) ) * link_information.alignment.x;
			y_offset = (link_dimensions_.h + link_information.padding * 4 + pos.y - (starting_rect->h + starting_rect->y) ) * link_information.alignment.y;
		}

		link_dimensions_.x -= x_offset;
		link_dimensions_.y -= y_offset;
		cursor_dimensions_ = SDL_Rect{ static_cast<int>(pos.x) + 2 * link_information.padding - x_offset, static_cast<int>(pos.y) + (link_dimensions_.h ) / 2 - y_offset, CURSOR_WIDTH, CURSOR_WIDTH };
		box_dimensions_ = SDL_Rect{ static_cast<int>(pos.x) - x_offset, static_cast<int>(pos.y) - y_offset, link_dimensions_.w + cursor_dimensions_.w + link_information.padding * 6, link_dimensions_.h + link_information.padding * 4};
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

class NoAssetLink : public Link
{
public:
	explicit NoAssetLink(Command * command)
		: command_(command), previous_state_(0)
	{}
	~NoAssetLink()
	{}

	void set_link_information(const LinkBuilder link_information, const Vector2D pos, const std::string asset = "", SDL_Rect * starting_rect = nullptr) override
	{
		text_ = "";
		font_ = link_information.font;

		link_dimensions_ = { static_cast<int>(pos.x), static_cast<int>(pos.y), 0, 0 };
		cursor_dimensions_ = { static_cast<int>(pos.x) + 2 * link_information.padding, static_cast<int>(pos.y) + (starting_rect->h - link_information.padding * 4) / 2, CURSOR_WIDTH, CURSOR_HEIGHT };
		box_dimensions_ = { static_cast<int>(pos.x), static_cast<int>(pos.y), cursor_dimensions_.w + link_information.padding * 2, starting_rect->h };
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
