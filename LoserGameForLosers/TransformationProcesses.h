#pragma once
#include "Process.h"
#include <string>
#include "Game.h"

class FadeInImage : public Process
{
	Uint8 alpha_;
	Entity * asset_;
public:
	FadeInImage(Entity * entity)
		: alpha_(0), asset_(entity)
	{}

	FadeInImage(std::string image_id, SDL_Rect dest)
		: alpha_(0)
	{
	}

	FadeInImage(std::string image_id, SDL_Rect dest, int round_number)
		: alpha_(0)
	{
		auto x = (round_number % 3) * NUMBER_WIDTH;
		auto y = (round_number / 3) * NUMBER_HEIGHT;

		SDL_Rect src = { x, y, NUMBER_WIDTH, NUMBER_HEIGHT };

	}

	bool do_work() override;

	float work_done() override { return static_cast<float>(alpha_) / 255.0f; }
};

class FadeOutImage : public Process
{
	Uint8 alpha_;
	Entity * asset_;
public:

	FadeOutImage(Entity * entity)
		: alpha_(255), asset_(entity)
	{}

	FadeOutImage(std::string image_id, SDL_Rect dest)
		: alpha_(255)
	{
	}

	FadeOutImage(std::string image_id, SDL_Rect dest, int round_number)
		: alpha_(255)
	{
		auto x = (round_number % 3) * NUMBER_WIDTH;
		auto y = (round_number / 3) * NUMBER_HEIGHT;

		SDL_Rect src = { x, y, NUMBER_WIDTH, NUMBER_HEIGHT };

	}

	bool do_work() override;

	float work_done() override { return 255 / std::abs(alpha_ - 255); }
};

class DisplayPrompt : public Process
{
	std::string prompt_id_, prompt_path_;
	SDL_Rect prompt_dest{ 0, 0, SCREEN_WIDTH, 160 };
public:
	DisplayPrompt(std::string prompt_id, std::string prompt_path)
		: prompt_id_(std::move(prompt_id)), prompt_path_(std::move(prompt_path))
	{
		Game::assets->add_texture(prompt_id, prompt_path.c_str());
	}

	bool do_work() override
	{
		Game::assets->create_prompt(&prompt_dest, 1, prompt_id_.c_str());
		return true;
	}

	float work_done() override
	{
		return 1;
	}
};

class DisplayRound : public Process
{
	std::string round_id, number_id, round_path, number_path;
	SDL_Rect num_src{};
	SDL_Rect round_dest{ 0, 0, 600, 160 };
	SDL_Rect num_dest{ 700, 0, 100, 160 };

public:
	DisplayRound(std::string rnd_id, std::string num_id, std::string rnd_path, std::string num_path, int round_number)
		: round_id(std::move(rnd_id)), number_id(std::move(num_id)), round_path(rnd_path), number_path(num_path)
	{
		Game::assets->add_texture(round_id, round_path.c_str());
		Game::assets->add_texture(number_id, number_path.c_str());
		auto x = (round_number % 3) * NUMBER_WIDTH;
		auto y = (round_number / 3) * NUMBER_HEIGHT;

		num_src = { x, y, 100, 160 };
	}

	bool do_work() override
	{
		Game::assets->create_prompt(&round_dest, 1, round_id.c_str());
		Game::assets->create_prompt(&num_dest, &num_src, 1, number_id.c_str());
		return true;
	}

	float work_done() override { return 1; }
};

class ClearPrompts : public Process
{
public:
	ClearPrompts()
	{}

	bool do_work() override
	{
		for (auto& p : manager.get_group(Game::group_prompts))
		{
			p->del_group(Game::group_prompts);
			p->destroy();
		}
		return true;
	}

	float work_done() override { return 1; }
};