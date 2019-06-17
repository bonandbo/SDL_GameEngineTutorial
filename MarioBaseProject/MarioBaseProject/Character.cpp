#include "Character.h"
#include "Texture2D.h"


Character::Character()
{
	m_Position = Vector2D();
	m_Renderer = nullptr;
	m_Texture = nullptr;
	m_Direction = DIRECTION::RIGHT;
}

Character::Character(SDL_Renderer* renderer, std::string path, Vector2D startPosition)
{
	m_Renderer = renderer;
	m_Position = startPosition;
	m_Direction = DIRECTION::RIGHT;
	m_Texture = new Texture2D(renderer);
	if (!m_Texture->LoadFromFile(path.c_str()))
	{
		LOG("Error here\n");
	}
}

Character::~Character()
{
	if (m_Renderer)
		m_Renderer = nullptr;

	// is this needed ?
	if (m_Texture)
	{
		delete m_Texture;
		m_Texture = nullptr;
	}
}

void Character::Render()
{
	if (m_Direction == DIRECTION::LEFT)
	{
		m_Texture->Render(m_Position, SDL_FLIP_HORIZONTAL);
	}
	else if (m_Direction == DIRECTION::RIGHT)
	{
		m_Texture->Render(m_Position, SDL_FLIP_NONE);
	}
}

void Character::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_Direction = DIRECTION::LEFT;
			m_Position.x -= MARIO_SPD; // is that true to put it here ?
			break;
		case SDLK_RIGHT:
			m_Direction = DIRECTION::RIGHT;
			m_Position.x += MARIO_SPD; // is that true to put it here ?
			break;
		}
		break;
	default:
		break;
	}
}

void Character::SetPosition(Vector2D pos)
{
	m_Position.x = pos.x;
	m_Position.y = pos.y;
}

Vector2D Character::GetPosition()
{
	return m_Position;
}
