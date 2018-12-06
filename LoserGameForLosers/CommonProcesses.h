#pragma once

class Delay : public Process
{
	;
	int total_delay_;
	Timer *timer;
public:
	Delay(int seconds)
		: total_delay_(seconds)
	{
		timer = new Timer();
	}

	bool do_work() override
	{
		if (!timer->is_started())
		{
			timer->start();
		}

		if (timer->get_ticks() >= total_delay_)
		{
			timer->stop();
			return true;
		}
		return false;
	}

	float work_done() override { return timer->get_ticks() / static_cast<float>(total_delay_); }
};


class ChangeController : public Process
{
	float work_complete_;
	Entity * player1_, *player2_;
	std::string new_controller_;
public:
	ChangeController(Entity * player_left, Entity * player_right, std::string new_controller)
		: player1_(player_left), player2_(player_right), new_controller_(new_controller)
	{}
	~ChangeController() {}

	bool do_work() override
	{
		std::cout << new_controller_ << std::endl;
		player1_->get_component<ControllerComponent>().change_controller(new_controller_);
		player2_->get_component<ControllerComponent>().change_controller(new_controller_);
		work_complete_ = 1;
		return true;
	}

	float work_done() override { return work_complete_; }
};

class ChangeStateProcess : public Process
{
	float work_complete_;
	game_states new_state_;
public:
	ChangeStateProcess(game_states new_state)
		: new_state_(new_state), work_complete_(0)
	{}

	bool do_work() override
	{
		Game::set_next_state(new_state_);
		work_complete_ = 1;
		return true;
	}

	float work_done() override { return work_complete_; }
};

class Skip : public Process
{
public:
	Skip() {}

	bool do_work() override { return true; }
	float work_done() override { return 1; }
};