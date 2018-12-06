#pragma once
#include "SDL.h"

class Timer
{
public:
	Timer();

	void start();
	void stop();

	void pause();
	void unpause();

	Uint32 get_ticks();

	bool is_started();
	bool is_paused();


private:
	Uint32 start_ticks_;

	Uint32 paused_ticks_;

	bool paused_;
	bool started_;
};