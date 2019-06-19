#include "SceneLevel1.h"
#include "Texture2D.h" // finally, we kept our promise
#include <iostream>
#include "Constants.h"
#include "LevelMap.h"
#include "PowBlock.h"
#include "Collisions.h"
#include "Character.h"
#include "CharacterMario.h"

SceneLevel1::SceneLevel1() : m_BackgroundTex(nullptr), m_Mario(nullptr), m_LevelMap(nullptr), m_PowBlock(nullptr) { }

SceneLevel1::SceneLevel1(SDL_Renderer* renderer) : Scene(renderer) 
{
	m_LevelMap = nullptr;
	m_PowBlock = nullptr;
	SetLevel();
}

SceneLevel1::~SceneLevel1()
{
	if (m_BackgroundTex)
	{
		delete m_BackgroundTex;
		m_BackgroundTex = nullptr;
	}

	if (m_PowBlock)
	{
		delete m_PowBlock;
		m_PowBlock = nullptr;
	}

	if (m_LevelMap)
	{
		delete m_LevelMap;
		m_LevelMap = nullptr;
	}

	if (m_Mario)
	{
		delete m_Mario;
		m_Mario = nullptr;
	}

	
}

void SceneLevel1::Render()
{
	// Draw the background texture
	m_BackgroundTex->Render(Vector2D(), SDL_FLIP_NONE);
	m_Mario->Render();
	m_PowBlock->Render();
}

void SceneLevel1::UpdatePowBlock(float deltaTime)
{
	if (m_PowBlock->IsAvailable())
	{
		// if collide
		if (Collisions::GetInstance()->Box(m_PowBlock->GetCollision(), m_Mario->GetCollisionBox()))
		{
			if (m_Mario->IsJumping())
			{
				DoScreenShake();
				m_PowBlock->TakeAHit();
				m_Mario->CancelJump(deltaTime);
			}
		}
	}
}

void SceneLevel1::DoScreenShake()
{

}
	
void SceneLevel1::Update(float deltaTime, SDL_Event e)
{
	UpdatePowBlock(deltaTime);
	m_Mario->Update(deltaTime, e);
}

void SceneLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = {  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
										{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	// clear up any old map
	if (m_LevelMap)
	{
		delete m_LevelMap;
	}

	// Set new one
	m_LevelMap = new LevelMap(map);
}

bool SceneLevel1::SetLevel()
{
	// Load the background texture
	m_BackgroundTex = new Texture2D(m_Renderer);
	std::string dest = std::string(FOLDER_IMG).append("/").append(BACKGROUND_IMG);

	if (!m_BackgroundTex->LoadFromFile(dest.c_str()))
	{
		LOG("Failed to load texture");
		return false;
	}

	// Set level map
	SetLevelMap();

	// Set up the character
	m_Mario = new CharacterMario(m_Renderer, std::string(FOLDER_IMG).append("/").append(MARIO_IMG).c_str(), Vector2D(64, INITIAL_POS_MARIO_Y), m_LevelMap);
	// why we handle update in character but pass the position here ?

	m_PowBlock = new PowBlock(m_Renderer, m_LevelMap, Vector2D());

	return true;
}

