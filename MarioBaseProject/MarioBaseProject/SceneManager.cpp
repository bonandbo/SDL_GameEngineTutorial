#include "SceneManager.h"
#include "Scene.h"
#include <iostream>
#include "SceneLevel1.h"

SceneMaganer::SceneMaganer()
{
	m_Renderer = nullptr;
	m_CurrentScene = nullptr;
}
SceneMaganer::SceneMaganer(SDL_Renderer* renderer, SCENES defaultScene)
{
	m_Renderer = renderer;
	ChangeScene(defaultScene); // to make sure the first scene is the start one
}

SceneMaganer::~SceneMaganer()
{
	if (m_Renderer)
		SDL_DestroyRenderer(m_Renderer);
	m_Renderer = nullptr;

	if (m_CurrentScene)
		delete m_CurrentScene;
	m_CurrentScene = nullptr;
}

void SceneMaganer::Render()
{
	m_CurrentScene->Render();
}

void SceneMaganer::Update(float deltaTime, SDL_Event e)
{
	m_CurrentScene->Update(deltaTime, e);
}

void SceneMaganer::ChangeScene(SCENES newScene)
{
	// clear the old screen
	if (m_CurrentScene)
	{
		delete m_CurrentScene;
	}

	SceneLevel1* tempScene;
	switch (newScene)
	{
	case SCENES::LEVEL_1:
		tempScene = new SceneLevel1(m_Renderer);
		m_CurrentScene = (Scene*)tempScene;
		tempScene = nullptr;
		break;
	default:
		break;
	}

}
