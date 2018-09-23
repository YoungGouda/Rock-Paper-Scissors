#include "stdafx.h"
#include "EndOfRoundLogic.h"
#include <cmath>

bool EndOfRoundLogic::CheckWinner()
{
	bool isWinner = false;
	//there's probably a better way
	float playerDistance = pPlayerTC->position.x - oPlayerTC->position.x;
	float priorityPlayerOperator = playerDistance / std::abs(playerDistance);

	float scaledPlayer = pPlayerTC->scale * SPRITE_LENGTH;

	float priorityPlayerWhifDistance = pPlayerPC->chosenAttack.whifDistance * pPlayerTC->scale * pPlayerTC->width;
	float otherPlayerWhifDistance = oPlayerPC->chosenAttack.whifDistance * oPlayerTC->scale * pPlayerTC->width;

	if (checOutRightVictor(pPlayerPC->chosenAttack, oPlayerPC->chosenAttack))
		isWinner = true;
	else
	{
		if (checkAttackInRange(oPlayerPC->chosenAttack, pPlayerPC->chosenAttack.whifDistance * scaledPlayer))
		{
			cleanUpRound(oPlayerPC, pPlayerPC);
			isWinner = true;
		}
	}
	return isWinner;
}

bool EndOfRoundLogic::CheckMatchWinner()
{
	bool isMatchWinner = false;
	if (pPlayerPC->numWins == ROUNDWIN)
		isMatchWinner = true;
	if (oPlayerPC->numWins == ROUNDWIN)
		isMatchWinner = true;
	return isMatchWinner;
}

bool EndOfRoundLogic::checOutRightVictor(Attack pPAtt, Attack oPAtt)
{
	bool outRightVictor = false;

	if ( (checkAttackInRange(pPAtt) || checkAttackInRange(oPAtt)) && pPAtt.animID == checkAttackWinner(pPAtt, oPAtt).animID)
	{
		cleanUpRound(pPlayerPC, oPlayerPC);
		outRightVictor = true;
	}
	else if ( (checkAttackInRange(pPAtt) || checkAttackInRange(oPAtt)) && oPAtt.animID == checkAttackWinner(pPAtt, oPAtt).animID)
	{
		cleanUpRound(oPlayerPC, pPlayerPC);
		outRightVictor = true;
	}
	return outRightVictor;
}

bool EndOfRoundLogic::checkAttackInRange(Attack att)
{
	float playerDistance = pPlayerTC->position.x - oPlayerTC->position.x;
	float attRange = att.Range * pPlayerTC->width * pPlayerTC->scale;

	return attRange >= std::abs(playerDistance);
}

bool EndOfRoundLogic::checkAttackInRange(Attack att, float updatedPostion)
{
	float playerDistance = pPlayerTC->position.x - oPlayerTC->position.x;
	float attRange = att.Range * pPlayerTC->width * pPlayerTC->scale;

	return attRange >= std::abs(playerDistance) - updatedPostion;
}



Attack EndOfRoundLogic::checkAttackWinner(Attack ppAtt, Attack opAtt)
{
	if (ppAtt.animID == opAtt.animID)
		return ppAtt;
	if (ppAtt.animID == "whip")
	{
		if (opAtt.animID == "jump kick")
			return opAtt;
		else
			return ppAtt;
	}
	if (ppAtt.animID == "jump kick")
	{
		if (opAtt.animID == "grab")
			return opAtt;
		else
			return ppAtt;
	}
	if (ppAtt.animID == "grab")
	{
		if (opAtt.animID == "whip")
			return opAtt;
		else
			return ppAtt;
	}
}
