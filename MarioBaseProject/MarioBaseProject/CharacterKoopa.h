#pragma once

#include <SDL.h>
#include "Character.h"
#include "Commons.h"

class LevelMap;
class Texture2D;

class CharacterKoopa : public Character // why public
{
public:
	CharacterKoopa(SDL_Renderer* render, std::string path, Vector2D position, LevelMap* map, DIRECTION direction, float movementSpd);
	~CharacterKoopa();

	void Update(float deltaTime, SDL_Event e);
	void Render();

	void TakeDamage();

private:
	void FlipRightwayUp();

	float	m_ASpriteWidth;
	float	m_ASpriteHeight;
	bool	m_IsInjured;
	float	m_InjuredTime;
};
