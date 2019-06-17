#pragma once

#include "Scene.h"

Scene::Scene()
{
	m_Renderer = nullptr;
}

Scene::Scene(SDL_Renderer* renderer)
{
	m_Renderer = renderer;
}

Scene::~Scene()
{
	if (m_Renderer)
		// SDL_DestroyRenderer(m_Renderer); // why not here ?
		m_Renderer = nullptr;
}

void Scene::Render()
{

}

void Scene::Update(float delta, SDL_Event e)
{

}
