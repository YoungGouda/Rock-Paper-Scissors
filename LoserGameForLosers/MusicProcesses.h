#pragma once
#include "Processes.h"

class PlaySound : public Process
{
	float work_complete_;
	Mix_Chunk * sound;
public:
	PlaySound(std::string id)
		: work_complete_(0)
	{
		sound = Game::assets->get_sound(id);
	}

	bool do_work() override
	{
		Mix_PlayChannel(-1, sound, 0);
		work_complete_ = 1;
		return true;
	}

	float work_done() override { return work_complete_; }
};

class PlayMusic : public Process
{
	float work_complete_;
	Mix_Music * music;
public:
	PlayMusic(std::string id)
		: work_complete_(0)
	{
		music = Game::assets->get_music(id);
	}

	bool do_work() override
	{
		Mix_PlayMusic(music, -1);
		work_complete_ = 1;
		return true;
	}

	float work_done() override { return work_complete_; }

};

class StopMusic : public Process
{
	float work_complete_;
public:
	StopMusic()
		: work_complete_(0)
	{}

	bool do_work() override
	{
		Mix_HaltMusic();
		work_complete_ = 1;
		return true;
	}

	float work_done() override { return work_complete_; }
};