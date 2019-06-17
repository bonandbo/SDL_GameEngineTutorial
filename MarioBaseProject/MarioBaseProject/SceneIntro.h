#pragma once

#include <SDL.h>
#include "Commons.h"
#include "Scene.h"

class Texture2D;

class SceneIntro : Scene
{
public:
	SceneIntro(SDL_Renderer* render);
	~SceneIntro();

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	Texture2D* m_Texture;
	bool SetBackgroundImage();
};
