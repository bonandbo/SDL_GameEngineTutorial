#pragma once

#include <SDL.h>
#include "Character.h"
#include "Commons.h"

class LevelMap;
class Texture2D;

class CharacterMario : public Character // why public
{
public:
	CharacterMario(SDL_Renderer* render, std::string path, Vector2D position, LevelMap* map);
	~CharacterMario();

	void Update(float deltaTime, SDL_Event e);

private:
	void HandleEvent(SDL_Event e);
};
