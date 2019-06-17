#include "SceneLevel1.h"
#include "Texture2D.h" // finally, we kept our promise
#include <iostream>


SceneLevel1::SceneLevel1() : m_BackgroundTex(nullptr) { }

SceneLevel1::SceneLevel1(SDL_Renderer* renderer) : Scene(renderer) 
{
	SetLevel();
}

SceneLevel1::~SceneLevel1()
{
	if (m_BackgroundTex)
	{
		delete m_BackgroundTex;
		m_BackgroundTex = nullptr;
	}
}

void SceneLevel1::Render()
{
	// Draw the background texture
	m_BackgroundTex->Render(Vector2D(), SDL_FLIP_NONE);
}
	
void SceneLevel1::Update(float deltaTime, SDL_Event e)
{

}

bool SceneLevel1::SetLevel()
{
	// Load the background texture
	m_BackgroundTex = new Texture2D(m_Renderer);
	std::string dest = "";
	dest = std::string(FOLDER_IMG);
	dest.append("/");
	dest.append(TEST_IMG);
	if (!m_BackgroundTex->LoadFromFile(dest.c_str()))
	{
		LOG("Failed to load texture");
		return false;
	}

	return true;
}

