#pragma once

#include <SDL.h>

#include "Character.h"
#include "Constants.h"

class CharacterAnimated : Character
{
public:
	CharacterAnimated(SDL_Renderer* renderer, std::string path, Vector2D position, LevelMap* map);
	~CharacterAnimated();

	void Render();
	void Update(float deltaTime, SDL_Event e);
private:
	void HandleEvent(SDL_Event e);
	void SetSpriteClip();

	float	m_ASpriteWidth;
	float	m_ASpriteHeight;
	SDL_Rect m_SpriteClips[STICKMAN_SPRITE_PER_FRAME];

	int m_Frame;
};
