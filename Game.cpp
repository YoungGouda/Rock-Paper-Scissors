#include "stdafx.h"


Manager manager;

BackgroundLogic * bgLogic;
EndOfRoundLogic * eorLogic;
SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;
KeyboardHandler* keyHandler = new KeyboardHandler();
AssetManager* Game::assets = new AssetManager(&manager);
bool Game::endOfRound = false;

bool Game::isRunning = false;
SDL_Scancode keys[3] = { SDL_SCANCODE_D, SDL_SCANCODE_A, SDL_SCANCODE_1};

auto& playerLeft(manager.addEntity());
auto& playerRight(manager.addEntity());
auto& background(manager.addEntity());
auto& backgroundRight(manager.addEntity());
auto& backgroundLeft(manager.addEntity());


void Game::init(const char * windowTitle)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}
		Game::isRunning = true;
	}

	assets->AddTexture("player", "Fighter_full.png");
	assets->AddTexture("background", "backgroundTake3.png");
	
	background.addComponent<TransformComponent>(0, BACKGROUND_Y_OFFSET, BACKGROUND_HEIGHT, BACKGROUND_WIDTH, BACKGROUND_SCALING);
	background.addComponent<BackgroundComponent>("background");
	background.addGroup(Game::groupBackground);

	backgroundRight.addComponent<TransformComponent>(background.getComponent<TransformComponent>().position.x + BACKGROUND_WIDTH, BACKGROUND_Y_OFFSET, BACKGROUND_HEIGHT, BACKGROUND_WIDTH, BACKGROUND_SCALING);
	backgroundRight.addComponent<BackgroundComponent>("background");
	backgroundRight.addGroup(Game::groupBackground);

	backgroundLeft.addComponent<TransformComponent>(background.getComponent<TransformComponent>().position.x - BACKGROUND_WIDTH, BACKGROUND_Y_OFFSET, BACKGROUND_HEIGHT, BACKGROUND_WIDTH, BACKGROUND_SCALING);
	backgroundLeft.addComponent<BackgroundComponent>("background");
	backgroundLeft.addGroup(Game::groupBackground);

	playerLeft.addComponent<TransformComponent>(SPRITE_LEFT_EDGE_OF_SCREEN, SPRITE_BOTTOM_OF_SCREEN, SPRITE_LENGTH, SPRITE_LENGTH, SPRITE_SCALING);
	playerLeft.addComponent<SpriteComponent>("player", true);
	playerLeft.addComponent<ControllerComponent>(PLAYER_VELOCITY);
	playerLeft.addComponent<PlayerComponent>(false, "Brunis");
	playerLeft.addGroup(Game::groupPlayers);

	playerRight.addComponent<TransformComponent>(SPRITE_RIGHT_EDGE_OF_SCREEN, SPRITE_BOTTOM_OF_SCREEN, SPRITE_LENGTH, SPRITE_LENGTH, SPRITE_SCALING);
	playerRight.addComponent<SpriteComponent>("player", 0, SDL_FLIP_HORIZONTAL, true);
	playerRight.addComponent<ControllerComponent>(PLAYER_PRIORITY_VELOCITY, keys);
	playerRight.addComponent<PlayerComponent>(true, "Goon");
	playerRight.addGroup(Game::groupPlayers);

	playerLeft.getComponent<PlayerComponent>().setLineColor(255, 0, 0);
	playerRight.getComponent<PlayerComponent>().setLineColor(0, 0, 255);

	playerLeft.getComponent<PlayerComponent>().chooseAttack("whip");
	playerRight.getComponent<PlayerComponent>().chooseAttack("jump kick");

	bgLogic = new BackgroundLogic(&playerLeft, &playerRight, &background, 4);
	eorLogic = new EndOfRoundLogic(&playerLeft, &playerRight);
}

auto& playerGroup = manager.getGroup(Game::groupPlayers);
auto& backgroundGroup = manager.getGroup(Game::groupBackground);

void Game::update()
{

	float player1X = playerLeft.getComponent<TransformComponent>().position.x;
	float player2X = playerRight.getComponent<TransformComponent>().position.x;

	manager.refresh();
	manager.update();

	bgLogic->ScreenChange(player1X, player2X);

	TransformComponent * centerbgTC = &background.getComponent<TransformComponent>();
	TransformComponent * rightbgTC = &backgroundRight.getComponent<TransformComponent>();
	TransformComponent * leftbgTC = &backgroundLeft.getComponent<TransformComponent>();

	
	// Sync backgrounds
	centerbgTC->setYPosition(SCREEN_HEIGHT - centerbgTC->height * centerbgTC->scale);
	rightbgTC->setYPosition(centerbgTC->position.y);
	leftbgTC->setYPosition(centerbgTC->position.y);

	rightbgTC->setXPosition(centerbgTC->position.x + centerbgTC->width * centerbgTC->scale);
	leftbgTC->setXPosition(centerbgTC->position.x - centerbgTC->width * centerbgTC->scale);

	rightbgTC->setScaling(centerbgTC->scale);
	leftbgTC->setScaling(centerbgTC->scale);

	/*if (!eorLogic->CheckWinner())
		std::cout << "Wow, a whif" << std::endl;*/
}

void Game::render()
{
	SDL_RenderClear(renderer);
	for(auto& b: backgroundGroup)
	{
		b->draw();
	}
	for (auto& p : playerGroup)
	{
		p->draw();
	}
	SDL_RenderPresent(renderer);
}

void Game::handleEvents()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;
	}
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

