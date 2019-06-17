#include "SceneIntro.h"
#include "Commons.h"
#include "Texture2D.h"

SceneIntro::SceneIntro(SDL_Renderer* render) : Scene(render)
{
	m_Texture = nullptr; 
	SetBackgroundImage();
}

SceneIntro::~SceneIntro()
{
	if (m_Texture)
	{
		delete m_Texture;
		m_Texture = nullptr;
	}
}

void SceneIntro::Render()
{
	m_Texture->Render(Vector2D(), SDL_FLIP_NONE);
}

void SceneIntro::Update(float deltaTime, SDL_Event e)
{

}

bool SceneIntro::SetBackgroundImage()
{
	m_Texture = new Texture2D(m_Renderer); // what happen with new Texture2D() => Invalid Renderer
	std::string dest = "";
	dest = std::string(FOLDER_IMG);
	dest.append("/");
	dest.append(BACKGROUND_IMG);
	if (!m_Texture->LoadFromFile(dest.c_str()))
	{
		LOG("Error load file in SceneIntro\n");
		return false;
	}
	return true;
}


