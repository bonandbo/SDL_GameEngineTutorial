#pragma once

#include "Commons.h"
#include <SDL.h>

class Scene;
class SceneLevel1;
class SceneIntro;

class SceneMaganer
{
public:
	SceneMaganer();
	SceneMaganer(SDL_Renderer* renderer, SCENES defaultScene);
	~SceneMaganer();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void ChangeScene(SCENES newScene);
private:
	SDL_Renderer* m_Renderer;
	Scene* m_CurrentScene;
	SceneLevel1* m_SceneLvl1;
	SceneIntro* m_SceneIntro;
};
