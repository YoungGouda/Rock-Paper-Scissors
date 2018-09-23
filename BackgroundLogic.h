#pragma once
#include "Components.h"



class BackgroundLogic
{
public:
	BackgroundLogic() = default;

	BackgroundLogic(Entity * player1, Entity * player2, Entity * background, int maxR) : maxRange(maxR)
	{
		p1TC = &player1->getComponent<TransformComponent>();
		p2TC = &player2->getComponent<TransformComponent>();
		bgTC = &background->getComponent<TransformComponent>();

		p1CC = &player1->getComponent<ControllerComponent>();
		p2CC = &player2->getComponent<ControllerComponent>();

		p1SC = &player1->getComponent<SpriteComponent>();
		p2SC = &player2->getComponent<SpriteComponent>();

		player1VelocityScale = p1CC->getVelocityScale();
		player2VelocityScale = p2CC->getVelocityScale();

		player1VelocityScaleDifference = player1VelocityScale - player2VelocityScale;
		player2VelocityScaleDifference = player2VelocityScale - player1VelocityScale;
	}

	~BackgroundLogic()
	{}

	void ScreenChange(float prevPlayer1X, float prevPlayer2X);

private:
	Manager* manager;

	TransformComponent * p1TC;
	TransformComponent * p2TC;
	TransformComponent * bgTC;

	ControllerComponent * p1CC;
	ControllerComponent * p2CC;

	SpriteComponent * p1SC;
	SpriteComponent * p2SC;

	int maxRange;

	float player1VelocityScale;
	float player2VelocityScale;

	float player1VelocityScaleDifference;
	float player2VelocityScaleDifference;

	void scrollScreenRight(float scrollIncrement);
	void scrollScreenLeft(float scrollIncrement);
	void stretchAssets(float stretch);
	void shrinkAssets(float shrink);

};