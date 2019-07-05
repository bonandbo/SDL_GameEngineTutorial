#include "Constants.h"
#include "Texture2D.h"
#include "Coin.h"
#include "LevelMap.h"

Coin::Coin(SDL_Renderer* renderer, std::string path, Vector2D pos, LevelMap* map)
{
	m_Renderer = renderer;
	m_Texture = new Texture2D(renderer);
	if (m_Texture->LoadFromFile(path))
	{
		m_ASpriteWidth = m_Texture->GetWidth() / NUMBER_OF_SPRITE_COIN;
		m_ASpriteHeight = m_Texture->GetHeight();
	}
	SetSpriteClip();
	m_Position = pos;
	m_Map = map;
	m_isMovingLeft = false;
	m_isAlive = false;
}

Coin::~Coin()
{
	if (m_Texture)
	{
		delete m_Texture;
		m_Texture = nullptr;
	}
	if (m_Renderer)
	{
		m_Renderer = nullptr;
	}
	if (m_Map)
	{
		m_Map = nullptr;
	}
}

void Coin::Render()
{
	if (m_isAlive)
	{
		SDL_Rect currentFrame = m_SpriteClip[m_Frame / 3];
		SDL_Rect destRect = { m_Position.x, m_Position.y, m_ASpriteWidth, m_ASpriteHeight };
		if (m_isMovingLeft)
		{
			m_Texture->Render(currentFrame, destRect, SDL_FLIP_NONE);
		}
		else
		{
			m_Texture->Render(currentFrame, destRect, SDL_FLIP_HORIZONTAL);
		}

#ifdef DEBUG_RENDER
		SDL_Rect dst = { (int)m_Position.x, (int)m_Position.y, (int)m_ASpriteWidth, (int)m_ASpriteHeight };
		SDL_SetRenderDrawColor(m_Renderer, 255, 24, 122, 0);
		SDL_RenderFillRect(m_Renderer, &dst);
#endif
	}
}

void Coin::Update(float deltaTime, SDL_Event e)
{
	float centralXPos = (m_Position.x + m_Texture->GetWidth() * 0.5f) / 48.0f;
	float yPos = (m_Position.y + m_Texture->GetHeight()) / 22.0f;

	if (m_Map->GetTileAt(yPos, centralXPos) == 0)
	{
		AddGravity(deltaTime, 300.0f);
	}
	else 
	{
		LOG("do something");
	}
	MoveHorizontal(deltaTime, 100.0f);
}

void Coin::SetSpriteClip()
{
	for (int i = 0; i < NUMBER_OF_SPRITE_COIN; i++)
	{
		m_SpriteClip[i].x = i * m_ASpriteWidth;
		m_SpriteClip[i].y = 0;
		m_SpriteClip[i].w = m_ASpriteWidth;
		m_SpriteClip[i].h = m_ASpriteHeight;
	}
}
    

void Coin::AddGravity(float deltaTime, float gravity)
{
	m_Position.y += gravity * deltaTime;
}

void Coin::MoveHorizontal(float deltaTime, float movementSpd)
{
	if (m_isMovingLeft)
	{
		m_Position.x -= (movementSpd * deltaTime);
	}
	else
	{
		m_Position.x += (movementSpd * deltaTime);
	}
}