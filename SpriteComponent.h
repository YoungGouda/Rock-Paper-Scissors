#pragma once

#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"
#include "Animation.h"
#include <map>




class SpriteComponent : public Component
{
private:
	TransformComponent * transform;
	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;
	std::string animID;
	int frames = 0;
	int speed = 200;
	int rotations = 0;

public:


	bool animated = false;
	int animIndex = 0;

	std::map<const char*, Animation > animations;

	SDL_RendererFlip spriteflip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	SpriteComponent(std::string id)
	{
		setTex(id);
	}

	SpriteComponent(std::string id, int rots, SDL_RendererFlip flp, bool isAnimated )
	{
		rotations = rots;
		spriteflip = flp;
		setTex(id);
		animated = isAnimated;

		Animation idle = Animation(0, 3, speed);
		Animation walk = Animation(1, 3, speed);

		animations.emplace("idle", idle);
		animations.emplace("walkLeft", walk);
		animations.emplace("walkRight", walk);
		Play("idle");

	}

	SpriteComponent(std::string id, bool isAnimated)
	{
		animated = isAnimated;
		setTex(id);
		Animation idle = Animation(0, 3, speed);
		Animation walk = Animation(1, 3, speed);

		animations.emplace("idle", idle);
		animations.emplace("walkLeft", walk);
		animations.emplace("walkRight", walk);
		Play("idle");
	
	}

	~SpriteComponent()
	{
	}

	void setTex(std::string id)
	{
		texture = Game::assets->GetTexture(id);
	}


	bool isAnimID(std::string aID)
	{
		return animID == aID;
	}

	SDL_Rect cloneAndReturnDestRect( int w)
	{
		SDL_Rect cloneRect;
		cloneRect.y = destRect.y;
		cloneRect.x = destRect.x;
		cloneRect.w = w;
		cloneRect.h = destRect.h;
		return cloneRect;
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}
	void update() override
	{
		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}
			
		srcRect.y = animIndex * transform->height;

		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, rotations, spriteflip);
	}

	void Play(const char* animName)
	{
		animID = animName;
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}
};