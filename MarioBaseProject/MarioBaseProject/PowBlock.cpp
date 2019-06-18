#include "PowBlock.h"
#include "Texture2D.h"
#include "LevelMap.h"
#include <iostream>
#include "Constants.h"

PowBlock::PowBlock()
{
	m_Renderer = nullptr;
	m_LevelMap = nullptr;
	m_Position = Vector2D();
	m_Texture = nullptr;
	m_Width = 0;
	m_Height = 0;
	m_NumberOfHitsLeft = 0;
}

PowBlock::PowBlock(SDL_Renderer* renderer, LevelMap* map, Vector2D position)
{
	m_Renderer = renderer;
	m_LevelMap = map;
	//m_Position = position;
	m_Position = Vector2D(SCREEN_WIDTH * 0.5f - m_Width * 0.5f, 260);

	std::string dest = std::string(FOLDER_IMG).append("/").append(POWBLOCK_IMG);
	m_Texture = new Texture2D(renderer);
	if (!m_Texture->LoadFromFile(dest.c_str()))
	{
		LOG("Can not load from file in powblock");
		return;
	}

	m_Width = m_Texture->GetWidth() / 3; //3 sprites
	m_Height = m_Texture->GetHeight();

	m_NumberOfHitsLeft = NUMBER_HIT_LEFT;
}

PowBlock::~PowBlock()
{
	if(m_Renderer)
	{
		// why not delete ?
		m_Renderer = nullptr;
	}

	if (m_Texture)
	{
		delete m_Texture;
		m_Texture = nullptr;
	}

	if (m_LevelMap)
	{
		// why not delete ?
		m_LevelMap = nullptr;
	}
}

void PowBlock::Render()
{
	if (IsAvailable())
	{
		// available then we draw
		// Get the portion of the spritesheet you want to draw
		int left = m_Width * (m_NumberOfHitsLeft - 1);
		//                              // x , y 
		SDL_Rect portionOfSpriteSheet = { left, 0, m_Width, m_Height };

		// destionation draw
		SDL_Rect destRect = { (int)m_Position.x, (int)m_Position.y, m_Width, m_Height }; 
		
		// draw
		m_Texture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);
	}
	else
	{
		// not available we are doing nothing
	}

#ifdef DEBUG_RENDER
	SDL_Rect dst = { (int)GetCollision().x, (int)GetCollision().y, (int)GetCollision().w, (int)GetCollision().h };
	SDL_SetRenderDrawColor(m_Renderer, 0, 255, 0, 0);
	SDL_RenderFillRect(m_Renderer, &dst);
#endif
}

void PowBlock::Update(float deltaTime)
{
	// doing nothing at this moment
}

Rect2D PowBlock::GetCollision()
{
	// return the collision, actually it's the texture size, but this texture is spritesheet => need to calculate again
	return Rect2D(m_Position.x, m_Position.y, m_Texture->GetWidth() / 3, m_Texture->GetHeight());
}

void PowBlock::TakeAHit()
{
	// everytime call this function we reduct number of hit left to 1
	m_NumberOfHitsLeft--;

	// if ensure it's not available => change title to 0
	if (m_NumberOfHitsLeft <= 0)
	{
		m_NumberOfHitsLeft = 0;
		m_LevelMap->ChangeTileAt(8, 7, 0);
		m_LevelMap->ChangeTileAt(8, 8, 0);
	}
}

bool PowBlock::IsAvailable()
{
	// if still can hit => available
	return m_NumberOfHitsLeft > 0;
}