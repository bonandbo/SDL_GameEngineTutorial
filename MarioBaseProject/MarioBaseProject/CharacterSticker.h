#pragma once
#include <SDL.h>
#include "Character.h"

class Texture2D;

class CharacterSticker : public Character
{
public:
	CharacterSticker(SDL_Renderer* render, std::string path, Vector2D position, LevelMap* map, DIRECTION direction, float movementSpd);
	~CharacterSticker();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void HandleEvent(SDL_Event e);

private:
	float m_ASpriteWidth;
	float m_ASpriteHeight;
};
