#pragma once
#include "Processes.h"
#include "ECS.h"
#include <vector>




struct CombatProcessor
{
	int current_task;
	CombatProcessor(Entity * player_left, Entity * player_right, Entity * background)
		: player_left_(player_left), player_right_(player_right), background_(background), process_size_(0), round_count_(0), current_task(0)
	{}

	~CombatProcessor() 
	{}

	void create_combat()
	{
		round_count_++;
		current_task = 0;
		tasks.clear();
		tasks.push_back(new Skip());
		tasks.push_back(new AndMultiProcessor({new ResetGame(player_left_, player_right_, background_), new ChangeController(player_left_, player_right_, "nothing") }));
		tasks.push_back(new DisplayRound("round", "number", "round.png", "numbers.png",  round_count_));
		tasks.push_back(new Delay(3000));
		tasks.push_back(new ClearPrompts());
		tasks.push_back(new AndMultiProcessor({ new DisplayPrompt("select attack", "selectattack.png"), new ChangeController(player_left_, player_right_, "select attack") }));
		tasks.push_back(new Delay(2000));
		tasks.push_back(new ClearPrompts());
		tasks.push_back(new Delay(4000));
		tasks.push_back(new AndMultiProcessor({ new DisplayPrompt("stop", "stop.png"), new ChangeController(player_left_, player_right_, "nothing") }));
		tasks.push_back(new Delay(500));
		tasks.push_back(new ClearPrompts());
		tasks.push_back(new DisplayPrompt("fight", "fight.png"));
		tasks.push_back(new Delay(1000));
		tasks.push_back(new AndMultiProcessor({ new ClearPrompts(), new ChangeController(player_left_, player_right_, "combat") }));
		tasks.push_back(new AndMultiProcessor({new Delay(5000), new CombatCollision(player_left_, player_right_)}));
		tasks.push_back(new AndMultiProcessor({ new StopRound(player_left_, player_right_), new DisplayPrompt("stop", "stop.png"),  new ChangeController(player_left_, player_right_, "nothing") }));
		tasks.push_back(new Delay(500));
		tasks.push_back(new ClearPrompts());
		tasks.push_back(new EndOfRoundSequence(player_left_, player_right_, this));
		tasks.push_back(new DrawAttackLines(player_left_, player_right_, 1000));
		tasks.push_back(new DisplayPrompt("miss", "miss.png"));
		tasks.push_back(new Delay(1000));
		tasks.push_back(new ClearPrompts());
		tasks.push_back(new CleanUp(player_left_, player_right_, this));
	}

	void end_of_round(Entity * winner)
	{
		tasks.clear();
		current_task = 0;
		tasks.push_back(new Skip());
		tasks.push_back(new DrawAttackLines(player_left_, player_right_, 1000));
		if (winner->get_component<SpriteComponent>().sprite_flip == SDL_FLIP_HORIZONTAL)
		{
			tasks.push_back(new DisplayPrompt("player 2 wins", "player2wins.png"));
		}
		else
		{
			tasks.push_back(new DisplayPrompt("player 1 wins", "player1wins.png"));
		}
		tasks.push_back(new Delay(2000));
		tasks.push_back(new ClearPrompts());
		tasks.push_back(new CleanUp(player_left_, player_right_, this));
	}
	
	void go_to_menu()
	{
		tasks.clear();
		current_task = 0;
		tasks.push_back(new Skip());
		tasks.push_back(new Delay(1000));
		tasks.push_back(new ChangeStateProcess(STATE_MENU));
	}

	void match_winner()
	{
		tasks.clear();
		current_task = 0;
		tasks.push_back(new Skip());
		if (player_left_->get_component<PlayerComponent>().num_wins >= ROUNDWIN)
			tasks.push_back(new DisplayPrompt("player 1 match win", "player1matchwin.png"));
		else
			tasks.push_back(new DisplayPrompt("player 2 match win", "plater2matchwin.png"));
		tasks.push_back(new Delay(2000));
		tasks.push_back(new ClearPrompts());
		tasks.push_back(new Delay(500));
		tasks.push_back(new ChangeStateProcess(STATE_MENU));

	}

	void next_process()
	{
		if (current_task < tasks.size())
			current_task++;
	}

	std::vector<Process *> tasks;

private:
	int round_count_, process_size_;
	Entity * player_left_, *player_right_, *background_;
};

