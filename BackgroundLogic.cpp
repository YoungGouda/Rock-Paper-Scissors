#include "stdafx.h"
#include <cmath>


void BackgroundLogic::ScreenChange(float prevPlayer1X, float prevPlayer2X)
{
	float leftEdge = 0;
	float rightEdge = (float)SCREEN_WIDTH - (float)p2TC->width * p2TC->scale;
	int bottom = SCREEN_HEIGHT - p1TC->height * p1TC->scale;

	//Sets players to the edges of the screen if they move off the background
	if (p1TC->position.x < leftEdge)
		p1TC->setXPosition(leftEdge);
	if (p2TC->position.x >(float)SCREEN_WIDTH - (float)p2TC->width * p2TC->scale)
		p2TC->setXPosition((float)SCREEN_WIDTH - (float)p2TC->width * p2TC->scale);
	p1TC->setYPosition(bottom);
	p2TC->setYPosition(bottom);

	bool player1WalkLeft = p1SC->isAnimID("walkLeft");
	bool player1WalkRight = p1SC->isAnimID("walkRight");
	bool player1Idle = p1SC->isAnimID("idle");
	bool player2WalkLeft = p2SC->isAnimID("walkLeft");
	bool player2WalkRight = p2SC->isAnimID("walkRight");
	bool player2Idle = p2SC->isAnimID("idle");
	bool player1OffScreen = p1TC->position.x < leftEdge + FLT_EPSILON;
	bool player2OffScreen = p2TC->position.x >= rightEdge - FLT_EPSILON;

	float playersDistance = (p2TC->position.x - ((float)p2TC->width * p2TC->scale) / 2) - p1TC->position.x + ((float)p1TC->width * p1TC->scale) / 2;
	bool isMaxRange = playersDistance / ((float)p1TC->width * p1TC->scale) > maxRange;
	
	

	// Stretch Assets
	if (
		player1OffScreen && p2TC->position.x >= (float)SCREEN_WIDTH - (float)p2TC->width * p2TC->scale
		&& (player1WalkLeft || player1Idle)
		&& (player2WalkRight || player2Idle)
		&& !(player1Idle && player2Idle)
		&& !isMaxRange && p1TC->scale > SPRITE_SCALING_TARGET
		)
	{
		/*std::cout << "EXPAND" << std::endl; */
		if (player1WalkLeft && player2WalkRight)
		{
			if (player1VelocityScaleDifference > 0)
				scrollScreenLeft(player1VelocityScaleDifference * p1TC->speed);
			if (player2VelocityScaleDifference > 0)
				scrollScreenRight(player2VelocityScaleDifference * p2TC->speed);
			stretchAssets((player1VelocityScale * p1TC->speed + player2VelocityScale * p2TC->speed));
		}
		if (player1WalkLeft && player2Idle)
		{
			scrollScreenLeft(player1VelocityScale * p1TC->speed );
			stretchAssets(player1VelocityScale * p1TC->speed);
		}
		if (player2WalkRight && player1Idle)
		{
			scrollScreenRight(player2VelocityScale * p2TC->speed );
			stretchAssets(player2VelocityScale * p2TC->speed );
		}

	}
	//Scroll Background Left
	else if (
			player1OffScreen && player1WalkLeft 
			&& (!(p2TC->position.x >= (float)SCREEN_WIDTH - (float)p2TC->width * p2TC->scale - FLT_EPSILON) || !player2WalkRight)
			)
	{
		/*std::cout << "SCROLL LEFT" << std::endl;*/
		if (player2Idle && !isMaxRange)
		{
			scrollScreenLeft(player1VelocityScale * p1TC->speed);
			p2TC->setXPosition(prevPlayer2X + player1VelocityScale * p1TC->speed * p1TC->scale / SPRITE_SCALING);
		}
		if (player2WalkLeft)
		{
			scrollScreenLeft(player1VelocityScale * p1TC->speed);
			if (prevPlayer2X - player2VelocityScaleDifference * p1TC->speed * p1TC->scale / SPRITE_SCALING < (float)SCREEN_WIDTH - (float)p2TC->width * p2TC->scale)
			{
				p2TC->setXPosition(prevPlayer2X - player2VelocityScaleDifference * p1TC->speed * p1TC->scale / SPRITE_SCALING);
			}
			else
				p2TC->setXPosition((float)SCREEN_WIDTH - (float)p2TC->width * p2TC->scale);
			if (player2VelocityScaleDifference > 0)
				shrinkAssets(player2VelocityScaleDifference * p2TC->speed);
			if (player1VelocityScaleDifference > 0 && p2TC->position.x >= (float)SCREEN_WIDTH - (float)p2TC->width * p2TC->scale && !isMaxRange)
				stretchAssets(player1VelocityScaleDifference * p1TC->speed);
		}
		if (player2WalkRight && !isMaxRange)
		{
			scrollScreenLeft(player1VelocityScale * p1TC->speed);
			p2TC->setXPosition(p2TC->position.x + player1VelocityScale * p1TC->speed * p1TC->scale / SPRITE_SCALING);
		}
	}
	// Scroll Background Right
	else if (
			(p2TC->position.x >= (float)SCREEN_WIDTH - (float)p2TC->width * p2TC->scale) && player2WalkRight
			&& (!player1OffScreen || !player1WalkLeft)
			)
	{
		/*std::cout << "SCROLL RIGHT" << std::endl;*/
		if (player1Idle && !isMaxRange)
		{
			scrollScreenRight(player2VelocityScale * p2TC->speed);
			p1TC->setXPosition(prevPlayer1X - player2VelocityScale * p2TC->speed * p1TC->scale / SPRITE_SCALING);
		}
		if (player1WalkRight)
		{
			scrollScreenRight(player1VelocityScale * p1TC->speed);
			if (prevPlayer1X + player1VelocityScaleDifference * p2TC->speed * p1TC->scale / SPRITE_SCALING > leftEdge)
			{
				p1TC->setXPosition(prevPlayer1X);
				if (p1TC->scale >= SPRITE_SCALING)
					p1TC->setXPosition(prevPlayer1X + player1VelocityScaleDifference * p2TC->speed * p1TC->scale / SPRITE_SCALING);
			}
			else
				p1TC->setXPosition(leftEdge);
			if (player1VelocityScaleDifference > 0)
				shrinkAssets(player1VelocityScaleDifference * p1TC->speed);
			if (player2VelocityScaleDifference > 0 && p1TC->position.x < leftEdge + FLT_EPSILON && !isMaxRange)
				stretchAssets(player2VelocityScaleDifference * p2TC->speed);
		}
		if (player1WalkLeft && !isMaxRange)
		{
			scrollScreenRight(player1VelocityScale * p1TC->speed);
			p1TC->setXPosition(p1TC->position.x - p2CC->getVelocityScale() * p2TC->speed * p1TC->scale / SPRITE_SCALING);
		}
	}
	// Shrink Assets
	else if (
			(player1WalkRight && player2Idle
			|| player2WalkLeft && player1Idle
			|| player1WalkRight && player2WalkLeft)
			&& p1TC->scale < SPRITE_SCALING
			)
	{
		/*std::cout << "SHRINK" << std::endl;*/
		if (player1WalkRight && player2WalkLeft)
		{
			shrinkAssets((player1VelocityScale * p1TC->speed + player1VelocityScale * p2TC->speed));
			if (player1VelocityScaleDifference > 0)
				scrollScreenRight(player1VelocityScaleDifference * p1TC->speed);
			if (player2VelocityScaleDifference > 0)
				scrollScreenLeft(player2VelocityScaleDifference * p2TC->speed);
		}
		if (player1WalkRight && player2Idle)
		{
			shrinkAssets((player1VelocityScale * p1TC->speed));
			scrollScreenRight(player1VelocityScale * p1TC->speed);
		}
		if (player2WalkLeft && player1Idle)
		{
			shrinkAssets((player2VelocityScale * p2TC->speed));
			scrollScreenLeft(player2VelocityScale * p2TC->speed);
		}
	}

	//Collision Detection
	if (Collision::AABB(p1SC->cloneAndReturnDestRect(p1TC->width / 2), p2SC->cloneAndReturnDestRect(p2TC->width / 2)))
	{
		
		if (player1VelocityScaleDifference > 0)
		{
			if (player2WalkRight && p2TC->position.x + player1VelocityScaleDifference * p1TC->speed < rightEdge)
				p2TC->setXPosition(p2TC->position.x + player1VelocityScaleDifference * p1TC->speed);
			if (prevPlayer2X + player1VelocityScaleDifference * p1TC->speed < rightEdge)
			{
				p2TC->setXPosition(prevPlayer2X + player1VelocityScaleDifference * p1TC->speed);
				p1TC->setXPosition(prevPlayer1X);
			}
			if (player1Idle && prevPlayer1X - player1VelocityScaleDifference * p2TC->speed > leftEdge)
			{
				p1TC->setXPosition(prevPlayer1X - player1VelocityScaleDifference * p2TC->speed);
				p2TC->setXPosition(prevPlayer2X);
			}
			if (player1Idle && p1TC->position.x < leftEdge + player1VelocityScaleDifference * p2TC->speed)
			{
				p1TC->setXPosition(prevPlayer1X);
				p2TC->setXPosition(prevPlayer2X);
				scrollScreenLeft(player1VelocityScaleDifference * p2TC->speed);
			}
			if (p2TC->position.x > rightEdge - player1VelocityScaleDifference * p1TC->speed)
			{
				p1TC->setXPosition(prevPlayer1X);
				p2TC->setXPosition(prevPlayer2X);
				scrollScreenRight(player1VelocityScaleDifference * p1TC->speed);
			}
		}
		if (player2VelocityScaleDifference > 0)
		{
			if(player1WalkLeft && p1TC->position.x - player2VelocityScaleDifference * p2TC->speed > leftEdge)
				p1TC->setXPosition(p1TC->position.x - player2VelocityScaleDifference * p2TC->speed);
			if (prevPlayer1X - player2VelocityScaleDifference * p2TC->speed > leftEdge)
			{
				p1TC->setXPosition(prevPlayer1X - player2VelocityScaleDifference * p2TC->speed);
				p2TC->setXPosition(prevPlayer2X);
			}
			if (player2Idle && prevPlayer2X + player2VelocityScaleDifference * p1TC->speed < rightEdge)
			{
				p2TC->setXPosition(prevPlayer2X + player2VelocityScale * p1TC->speed);
				p1TC->setXPosition(prevPlayer1X);
			}
			if (player2Idle && p2TC->position.x > rightEdge - player2VelocityScaleDifference * p1TC->speed)
			{
				p1TC->setXPosition(prevPlayer1X);
				p2TC->setXPosition(prevPlayer2X);
				scrollScreenRight(player2VelocityScaleDifference * p2TC->speed);
			}
			if (p1TC->position.x < leftEdge + player2VelocityScaleDifference * p1TC->speed)
			{
				p1TC->setXPosition(prevPlayer1X);
				p2TC->setXPosition(prevPlayer2X);
				scrollScreenLeft(player2VelocityScaleDifference * p2TC->speed);
			}
		}
			
	}

}

void BackgroundLogic::scrollScreenRight(float scrollIncrement)
{
	bgTC->setXPosition(bgTC->position.x - scrollIncrement * p1TC->scale / SPRITE_SCALING);
	/*if (bgTC->position.x < -bgTC->width * bgTC->scale)
		bgTC->setXPosition(0);*/
}

void BackgroundLogic::scrollScreenLeft(float scrollIncrement)
{
	bgTC->setXPosition(bgTC->position.x + scrollIncrement * p1TC->scale / SPRITE_SCALING);
	/*if (bgTC->position.x > bgTC->width * bgTC->scale)
		bgTC->setXPosition(0);*/
}

void BackgroundLogic::stretchAssets(float stretch)
{
	// the difference between scale bounds / the possible distance traveled by a single character * stretch speed
	float playerScRange = (SPRITE_SCALING - SPRITE_SCALING_TARGET) / (float)(SCREEN_WIDTH - SPRITE_SCALED) * -stretch * p1TC->scale / SPRITE_SCALING;
	float backgroundScRange = (BACKGROUND_SCALING - BACKGROUND_SCALING_TARGET) / (float)(SCREEN_WIDTH - SPRITE_SCALED) * -stretch * bgTC->scale / BACKGROUND_SCALING;

	p1TC->setScaling(std::max(SPRITE_SCALING_TARGET, p1TC->scale + playerScRange ));

	float scalingOffsetX = p2TC->width * p2TC->scale - (p2TC->scale + playerScRange) * p2TC->width;

	
	if (SPRITE_SCALING_TARGET < p2TC->scale)
		p2TC->setXPosition(p2TC->position.x + scalingOffsetX * (SPRITE_LENGTH * p2TC->scale) / (SPRITE_LENGTH * std::max(SPRITE_SCALING_TARGET, p2TC->scale + playerScRange) ) );

	p2TC->setScaling(std::max(SPRITE_SCALING_TARGET, p2TC->scale + playerScRange));

	scalingOffsetX = bgTC->width * bgTC->scale - (bgTC->scale + backgroundScRange) * bgTC->width;

	const float scalingOffsetY = bgTC->height * bgTC->scale - (bgTC->scale + backgroundScRange) * bgTC->height;

	bgTC->setScaling(std::min(BACKGROUND_SCALING, bgTC->scale + backgroundScRange));

	float cosAngleBackground = std::abs( (stretch * (-bgTC->position.x + SCREEN_HALF_WIDTH) ) * (SCREEN_HALF_WIDTH * (BACKGROUND_WIDTH * bgTC->scale  ) )
		/ (std::pow(std::pow(stretch * (-bgTC->position.x + SCREEN_HALF_WIDTH), 2), 0.5) * std::pow(std::pow(scalingOffsetX * (BACKGROUND_WIDTH * bgTC->scale - SCREEN_HALF_WIDTH - std::abs(bgTC->position.x)), 2) + std::pow(scalingOffsetY * bgTC->position.y, 2), 0.5) ) );

	std::cout << "cosBackgroundAngle: " << cosAngleBackground << std::endl;
	// to account for stretching position changes

	// the difference in scaling from new and old backgrounds / the center of stretch = goddamn stretching miracle
	if (BACKGROUND_SCALING_TARGET < bgTC->scale)
		bgTC->setXPosition(
			bgTC->position.x + scalingOffsetX * (-bgTC->position.x + SCREEN_HALF_WIDTH)
			/ (BACKGROUND_WIDTH * bgTC->scale)
		);
}

void BackgroundLogic::shrinkAssets(float shrink)
{
	// the difference between scale bounds / the possible distance traveled by a single character * stretch speed
	float playerScRange = (SPRITE_SCALING - SPRITE_SCALING_TARGET) / (float)(SCREEN_WIDTH - SPRITE_SCALED) * shrink * p1TC->scale / SPRITE_SCALING;
	float backgroundScRange = (BACKGROUND_SCALING - BACKGROUND_SCALING_TARGET) / (float)(SCREEN_WIDTH - SPRITE_SCALED) * shrink * bgTC->scale / BACKGROUND_SCALING;

	p1TC->setScaling(std::min(SPRITE_SCALING, p1TC->scale + playerScRange));

	float scalingOffsetX = p2TC->width * p2TC->scale - (p2TC->scale + playerScRange) * p2TC->width;


	// to account for stretching position changes
	if (SPRITE_SCALING_TARGET < p2TC->scale)
		p2TC->setXPosition(p2TC->position.x + scalingOffsetX * (SPRITE_LENGTH * p2TC->scale ) / (SPRITE_LENGTH * std::min(SPRITE_SCALING, p2TC->scale + playerScRange ) ) );

	p2TC->setScaling(std::min(SPRITE_SCALING, p2TC->scale + playerScRange));

	scalingOffsetX = bgTC->width * bgTC->scale - (bgTC->scale + backgroundScRange) * bgTC->width;

	float scalingOffsetY = bgTC->height * bgTC->scale - (bgTC->scale + backgroundScRange) * bgTC->height;

	bgTC->setScaling(std::min(BACKGROUND_SCALING, bgTC->scale + backgroundScRange));

	//float cosAngleBackground = ((-bgTC->position.x) * bgTC->scale) * ((-bgTC->position.x + BACKGROUND_WIDTH) * bgTC->scale)
	//	/ (std::pow(std::pow((-bgTC->position.x) *bgTC->scale, 2), 0.5) * std::pow(std::pow((-bgTC->position.x + BACKGROUND_WIDTH) * bgTC->scale, 2) + std::pow((BACKGROUND_HEIGHT - SCREEN_HEIGHT) *bgTC->scale, 2), 0.5));
	
	float cosAngleBackground = std::abs(((-bgTC->position.x + SCREEN_HALF_WIDTH)) * (scalingOffsetX * ( std::abs(bgTC->position.x) - BACKGROUND_WIDTH * bgTC->scale))
								/ (std::pow(std::pow(shrink * (-bgTC->position.x + SCREEN_HALF_WIDTH), 2), 0.5) *
									std::pow(std::pow(scalingOffsetX * (BACKGROUND_WIDTH * bgTC->scale - SCREEN_HALF_WIDTH - std::abs(bgTC->position.x + bgTC->scale * bgTC->height)), 2)
										+ std::pow(scalingOffsetY * bgTC->position.y, 2), 0.5)));

	std::cout << "cosBackgroundAngle: " << cosAngleBackground << std::endl;

	// the difference in scaling from new and old backgrounds / the center of stretch = goddamn shrinking miracle
	if (BACKGROUND_SCALING > bgTC->scale )
		bgTC->setXPosition(
			bgTC->position.x + scalingOffsetX * (-bgTC->position.x + SCREEN_HALF_WIDTH)
			/ (BACKGROUND_WIDTH * bgTC->scale)
		);
}
