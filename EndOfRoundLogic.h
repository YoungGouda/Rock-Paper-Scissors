#pragma once
#include "Components.h"
#include "Attack.h"

class EndOfRoundLogic
{
public:
	EndOfRoundLogic() = default;

	EndOfRoundLogic(Entity * player1, Entity * player2)
	{
		pPlayerTC = &player1->getComponent<TransformComponent>();
		oPlayerTC = &player2->getComponent<TransformComponent>();

		pPlayerPC = &player1->getComponent<PlayerComponent>();
		oPlayerPC = &player2->getComponent<PlayerComponent>();

		pPlayerSC = &player1->getComponent<SpriteComponent>();
		oPlayerSC = &player2->getComponent<SpriteComponent>();
		if (player2->getComponent<PlayerComponent>().PriorityPlayer)
		{
			pPlayerTC = &player2->getComponent<TransformComponent>();
			oPlayerTC = &player1->getComponent<TransformComponent>();

			pPlayerPC = &player2->getComponent<PlayerComponent>();
			oPlayerPC = &player1->getComponent<PlayerComponent>();

			pPlayerSC = &player2->getComponent<SpriteComponent>();
			oPlayerSC = &player1->getComponent<SpriteComponent>();
		}
	}
	~EndOfRoundLogic()
	{}

	bool CheckWinner();
	bool CheckMatchWinner();

	Attack checkAttackWinner(Attack ppAtt, Attack opAtt);
private:
	TransformComponent * pPlayerTC;
	TransformComponent * oPlayerTC;
	SpriteComponent * pPlayerSC;
	SpriteComponent * oPlayerSC;
	PlayerComponent * pPlayerPC;
	PlayerComponent * oPlayerPC;
	bool checOutRightVictor(Attack ppAtt, Attack opAtt);
	bool checkAttackInRange(Attack att);
	bool checkAttackInRange(Attack att, float updatedPosition);
	void cleanUpRound(PlayerComponent * wPlayerPC, PlayerComponent * lPlayerPC)
	{
		/*wPlayerPC->roundWin();
		wPlayerPC->switchPriority();
		lPlayerPC->switchPriority();*/
		std::cout << "Round Winner: " << wPlayerPC->playerName << std::endl;
		if (CheckMatchWinner())
			std::cout << "Congratulations " << wPlayerPC->playerName << std::endl;
	}
};