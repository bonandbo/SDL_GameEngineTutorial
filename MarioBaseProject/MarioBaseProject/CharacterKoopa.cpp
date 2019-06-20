#include "CharacterKoopa.h"
#include "Texture2D.h"
#include "Constants.h"
#include "LevelMap.h"

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, std::string path, Vector2D position, LevelMap* map, DIRECTION direction, float movementSpd)
	: Character(renderer, path, position, map)
{
	m_Direction = direction;
	m_MovementSpeed = movementSpd;
	m_IsInjured = false;
	m_ASpriteWidth = (float)m_Texture->GetWidth() / 2; 
	m_ASpriteHeight = (float)m_Texture->GetHeight();
}

CharacterKoopa::~CharacterKoopa()
{

}

void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{
	// function as any character
	Character::Update(deltaTime, e);

	// handle the only happen logic for Koopa
	if (!m_IsInjured)
	{
		// Not injured then we move
		MoveHorizontal(deltaTime);
	}
	else
	{
		// stop moving
		m_IsMoving = false;

		// count the time injured
		m_InjuredTime -= deltaTime;
		if (m_InjuredTime <= 0.0f)
		{
			FlipRightwayUp();
		}
	}
}

void CharacterKoopa::Render()
{
	// variable to hold the left position of the sprite we want to draw
	float left = 0.0f;

	// If injured, move the left position to the next one
	if (m_IsInjured)
	{
		left = m_ASpriteWidth;
	}

	// Get the portion of spritesheet to draw
	SDL_Rect srcRect = { (int)left, 0, (int)m_ASpriteWidth, (int)m_ASpriteHeight };

	// Where to draw
	SDL_Rect destRect = { (int)m_Position.x, (int)m_Position.y, (int)m_ASpriteWidth, (int)m_ASpriteHeight };

	// draw
	if (m_Direction == DIRECTION::RIGHT)
	{
		m_Texture->Render(srcRect, destRect, SDL_FLIP_NONE);
	}
	else
	{
		m_Texture->Render(srcRect, destRect, SDL_FLIP_HORIZONTAL);
	}
}

void CharacterKoopa::TakeDamage()
{
	m_IsInjured = true;
	m_InjuredTime = INJURED_TIME;
	Jump();
}


void CharacterKoopa::FlipRightwayUp()
{
	if (m_Direction == DIRECTION::LEFT)
	{
		m_Direction = DIRECTION::RIGHT;
	}
	else
	{
		m_Direction = DIRECTION::LEFT;
	}		
	m_IsInjured = false;
	Jump();
}