#pragma once

#include "SDL.h"
#include <iostream>
#include "Commons.h"

class Texture2D;

class Character
{
public:
	Character();
	Character(SDL_Renderer* renderer, std::string path, Vector2D startPosition);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void SetPosition(Vector2D pos);
	Vector2D GetPosition();
private:
	SDL_Renderer* m_Renderer;
	Vector2D m_Position;
	Texture2D* m_Texture;
	DIRECTION m_Direction;
};
