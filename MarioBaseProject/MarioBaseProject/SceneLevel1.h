#pragma once

#include "Commons.h"
#include "SDL.h"
#include "Scene.h"

class Texture2D; // promise to compiler
// what if we dont

class SceneLevel1 : Scene
{
public:
	SceneLevel1();
	SceneLevel1(SDL_Renderer* renderer);
	~SceneLevel1();

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	Texture2D* m_BackgroundTex;
	bool SetLevel();

};
