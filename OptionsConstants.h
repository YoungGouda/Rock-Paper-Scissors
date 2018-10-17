#pragma once
#include "Command.h"


enum LINKS
{
	free_play,
	volume,
	difficulty,
	new_game,
	attack
};

struct Option
{
	Option(const int link)
		: link(link)
	{}
	Vector2D position;
	int link;
};

struct LinkBuilder
{
	LinkBuilder(const int padding, const Vector2D alignment, const Vector2D starting_position, const char * font)
	: padding(padding), alignment(alignment), starting_position(starting_position), font(font)
	{}
	int padding;
	Vector2D alignment; 
	Vector2D starting_position;
	std::string font;
};

struct Choices
{
	Choices(): link_parameters(5, Vector2D(0,0), Vector2D(0,0), "gil sans normal")
	{
	}

	Choices(const std::vector<std::vector<Option>> options, const LinkBuilder link_builder)
		: link_parameters(link_builder), options(options)
	{}

	LinkBuilder link_parameters;
	std::vector<std::vector<Option>> options{};
};