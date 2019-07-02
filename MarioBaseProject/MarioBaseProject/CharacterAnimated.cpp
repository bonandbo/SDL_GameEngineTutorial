#include "CharacterAnimated.h"
#include "Texture2D.h"

CharacterAnimated::CharacterAnimated(SDL_Renderer* renderer, std::string path, Vector2D position, LevelMap* map)
	: Character(renderer, path, position, map)
{
	m_ASpriteWidth = (float)m_Texture->GetWidth() / STICKMAN_SPRITE_PER_FRAME;
	m_ASpriteHeight = (float)m_Texture->GetHeight();
	m_Frame = 0; // first frame
	SetSpriteClip();
	printf("%d\n", 31 / 4);
}

CharacterAnimated::~CharacterAnimated()
{

}

void CharacterAnimated::SetSpriteClip()
{
	for (int i = 0; i < STICKMAN_SPRITE_PER_FRAME; i++)
	{
		m_SpriteClips[i].x = i * m_ASpriteWidth;
		m_SpriteClips[i].y = 0;
		m_SpriteClips[i].w = m_ASpriteWidth;
		m_SpriteClips[i].h = m_ASpriteHeight;
	}
}

void CharacterAnimated::Render()
{
	// current frame
	SDL_Rect currentClip = m_SpriteClips[m_Frame / 600];
	SDL_Rect destRect = { m_Position.x, m_Position.y, m_ASpriteWidth, m_ASpriteHeight };
	if (m_Direction == DIRECTION::LEFT)
	{
		m_Texture->Render(currentClip, destRect, SDL_FLIP_NONE);
	}
	else
	{
		m_Texture->Render(currentClip, destRect, SDL_FLIP_HORIZONTAL);
	}
}

void CharacterAnimated::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

	if (m_Position.x + m_ASpriteWidth >= SCREEN_WIDTH)
	{
		m_Direction = DIRECTION::LEFT;
		m_IsMovingLeft = true;
	}
	if (m_Position.x <= 0)
	{
		m_Direction = DIRECTION::RIGHT;
		m_IsMovingLeft = false;
	}

	MoveHorizontal(deltaTime);

	++m_Frame;
	if (m_Frame / 600 >= 4)
		m_Frame = 0;
}


void CharacterAnimated::HandleEvent(SDL_Event e)
{

}