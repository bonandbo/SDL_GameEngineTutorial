#pragma once

#include <SDL.h>

class Scene
{
public:
	Scene();
	Scene(SDL_Renderer* renderer);
	~Scene();

	virtual void Render();
	virtual void Update(float delta, SDL_Event e);
protected:
	SDL_Renderer* m_Renderer;
};