#include "SceneLevel1.h"
#include "Texture2D.h" // finally, we kept our promise
#include <iostream>
#include "Constants.h"
#include "LevelMap.h"
#include "PowBlock.h"
#include "Collisions.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterKoopa.h"
#include "CharacterAnimated.h"
#include "Coin.h"

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

	// clear vector
	m_Enemies.clear(); // is it enough ?
}

void SceneLevel1::Render()
{
	// Draw the background texture
	m_BackgroundTex->Render(Vector2D(), SDL_FLIP_NONE);
	m_Mario->Render();
	m_PowBlock->Render();
	// draw the enemies
	for (size_t i = 0; i < m_Enemies.size(); i++)
	{
		m_Enemies[i]->Render();
	}
	//m_Animated->Render();
	if (m_Coin)
	{
		m_Coin->Render();
	}
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
	for (auto enemy : m_Enemies)
	{
		enemy->TakeDamage();
	}
}

void SceneLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	// if we have enemy then update
	if (!m_Enemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (size_t i = 0; i < m_Enemies.size(); i++)
		{
			// Check if enemy is on the bottome row of tiles
			if (m_Enemies[i]->GetPosition().y >= MAP_1_BOTTOM_ROW)
			{
				// check if enemy out of screen
				if (m_Enemies[i]->GetPosition().x > SCREEN_WIDTH
					|| m_Enemies[i]->GetPosition().x < m_Enemies[i]->GetPosition().x + m_Enemies[i]->GetCollisionBox().w)
				{
					// all die
					m_Enemies[i]->SetAlive(false);
				}
			}
			
			// Update Enenmies
			m_Enemies[i]->Update(deltaTime, e);

			// Check to see if collide
			if (Collisions::GetInstance()->Box(m_Enemies[i]->GetCollisionBox(), m_Mario->GetCollisionBox()))
			{
				//m_Mario->SetState(STATES::CHARACTER_PLAYER_DEATH);
				m_Mario->SetAlive(false);
			}

			if (!m_Enemies[i]->IsAlive())
			{
				enemyIndexToDelete = i;
			}
		}

		// remove the dead one
		if (enemyIndexToDelete != -1)
		{
			m_Enemies.erase(m_Enemies.begin() + enemyIndexToDelete);
		}
	}
}

void SceneLevel1::CreateKoopa(Vector2D pos, DIRECTION direction, float speed)
{

	CharacterKoopa* koopa = new CharacterKoopa(m_Renderer, 
												std::string(FOLDER_IMG).append("/").append(KOOPA_IMG).c_str(), 
												pos, 
												m_LevelMap, 
												direction, 
												speed);
	m_Enemies.push_back(koopa);
	koopa = nullptr; // is this true ?
}

	
void SceneLevel1::Update(float deltaTime, SDL_Event e)
{
	UpdatePowBlock(deltaTime);
	UpdateEnemies(deltaTime, e);
	UpdateCoin(deltaTime, e);
	m_Mario->Update(deltaTime, e);
	//m_Animated->Update(deltaTime, e);
}

void SceneLevel1::SetLevelMap()
{
	// clear up any old map
	if (m_LevelMap)
	{
		delete m_LevelMap;
	}

	// Set new one
	m_LevelMap = new LevelMap(std::string(FOLDER_LEVEL).append("/").append(MAP_LEVEL_1));
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

	CreateKoopa(Vector2D(150, 32), DIRECTION::RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), DIRECTION::LEFT, KOOPA_SPEED);
	
	//CreateCharacterAnimated(Vector2D(200, 110));

	return true;
}

//void SceneLevel1::CreateCharacterAnimated(Vector2D pos)
//{
//	m_Animated = new CharacterAnimated(m_Renderer, std::string(FOLDER_IMG).append("/").append(ANIMATED_IMG).c_str(), pos, m_LevelMap);
//}

void SceneLevel1::SpawnCoin(std::vector<Vector2D> vPosition)
{

}

void SceneLevel1::SpawnCoin(Vector2D pos)
{
	if (!m_Coin)
	{
		m_Coin = new Coin(m_Renderer, std::string(FOLDER_IMG).append("/").append(COIN_IMG), pos, m_LevelMap);
		m_Coin->SetIsAlive(true);
	}
}

void SceneLevel1::UpdateCoin(float deltaTime, SDL_Event e)
{
	SpawnCoin(Vector2D());
	if (m_Coin != nullptr)
	{
		if (m_Coin->GetPosition().x + m_Coin->GetWidth() > SCREEN_WIDTH
					|| m_Coin->GetPosition().x < 0
					|| m_Coin->GetPosition().y < 0
					|| m_Coin->GetPosition().y > SCREEN_HEIGHT)
		{
			m_Coin->SetIsAlive(true);
			m_Coin->SetPosition(Vector2D(0, m_Coin->GetPosition().y));
			//delete m_Coin;
			//m_Coin = nullptr;
		}
		else
		{
			if (Collisions::GetInstance()->Circle(Circle2D(m_Mario->GetPosition().x, m_Mario->GetPosition().y, m_Mario->GetCollisionRadius()), 
												Circle2D(m_Coin->GetPosition().x, m_Coin->GetPosition().y, m_Coin->GetCollisionRadius())))
			{
				m_Coin->SetIsAlive(false);
				delete m_Coin;
				m_Coin = nullptr;
			}
		}
	}
	if(m_Coin)
		m_Coin->Update(deltaTime, e);
}


