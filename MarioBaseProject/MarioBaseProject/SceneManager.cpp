#include "SceneManager.h"
#include "Scene.h"
#include <iostream>
#include "SceneLevel1.h"
#include "SceneIntro.h"

SceneMaganer::SceneMaganer()
{
	m_Renderer = nullptr;
	m_CurrentScene = nullptr;
	m_SceneIntro = nullptr;
	m_SceneLvl1 = nullptr;
}
SceneMaganer::SceneMaganer(SDL_Renderer* renderer, SCENES defaultScene)
{
	m_Renderer = renderer;
	m_CurrentScene = nullptr;
	m_SceneIntro = nullptr;
	m_SceneLvl1 = nullptr;
	//m_SceneLvl1 = new SceneLevel1(renderer); // why not here
	//m_SceneIntro = new SceneIntro(renderer); // why not here
	ChangeScene(defaultScene); // to make sure the first scene is the start one
}

SceneMaganer::~SceneMaganer()
{
	if (m_SceneLvl1)
	{
		// delete m_SceneLvl1; // why ?
		m_SceneLvl1 = nullptr;
	}


	if (m_SceneIntro)
	{
		// delete m_SceneIntro; why?
		m_SceneIntro = nullptr;
	}

	if (m_CurrentScene)
	{
		delete m_CurrentScene; // why ?
		m_CurrentScene = nullptr;
	}
		

	if (m_Renderer)
		// why ? // SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
}

void SceneMaganer::Render() // should only pass renderer here
{
	m_CurrentScene->Render();
}

void SceneMaganer::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_i:
			ChangeScene(SCENES::INTRO);
			break;
		case SDLK_1:
			ChangeScene(SCENES::LEVEL_1);
			break;
		}
		break;
	default:
		break;
	}
	m_CurrentScene->Update(deltaTime, e);
}

void SceneMaganer::ChangeScene(SCENES newScene)
{
	// clear the old screen
	if (m_CurrentScene)
	{
		delete m_CurrentScene;
	}

	//SceneLevel1* tempLvl1; // how about htis ?
	//SceneIntro* tempIntro;
	switch (newScene)
	{
	case SCENES::LEVEL_1:
	{
		m_SceneLvl1 = new SceneLevel1(m_Renderer); // leave it here ???
		m_CurrentScene = (Scene*)m_SceneLvl1;
		//m_SceneLvl1 = nullptr;
		break;
	}
	case SCENES::INTRO:
	{
		m_SceneIntro = new SceneIntro(m_Renderer);
		m_CurrentScene = (Scene*)m_SceneIntro;
		//m_SceneIntro = nullptr;
		break;
	}
	default:
		break;
	}

}
