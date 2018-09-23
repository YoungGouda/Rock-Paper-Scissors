#pragma once

#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"
#include <map>
#include "AssetManager.h"
#include "Constants.h"


class BackgroundComponent : public Component
{
private:
	TransformComponent * transform;
	SDL_Texture *texture;
	SDL_Rect srcRect, destRec;
	int rotations = 0;

public:


	SDL_RendererFlip spriteflip = SDL_FLIP_NONE;

	BackgroundComponent() = default;
	BackgroundComponent(std::string id)
	{
		setTex(id);
	}

	BackgroundComponent(std::string id, int rots, SDL_RendererFlip flp)
	{
		rotations = rots;
		setTex(id);
		spriteflip = flp;
	}

	~BackgroundComponent()
	{
	}

	SDL_Rect getSrcRect()
	{
		return srcRect;
	}

	void setTex(std::string id)
	{
		texture = Game::assets->GetTexture(id);
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
		destRec.x = static_cast<int>(transform->position.x);
		destRec.y = static_cast<int>(transform->position.y);
		destRec.w =  transform->width * transform->scale;
		destRec.h = transform->height * transform->scale;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRec, rotations, spriteflip);
	}
};