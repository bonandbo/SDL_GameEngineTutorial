#include "Character.h"
#include "Texture2D.h"


Character::Character()
{
	m_Position = Vector2D();
	m_Renderer = nullptr;
	m_Texture = nullptr;
	m_Direction = DIRECTION::RIGHT;
	m_IsMovingLeft = false;
	m_IsMoving = false;
}

Character::Character(SDL_Renderer* renderer, std::string path, Vector2D startPosition)
{
	m_Renderer = renderer;
	m_Position = startPosition;
	m_Direction = DIRECTION::RIGHT;
	m_IsMovingLeft = false;
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

void Character::MoveHorizontal(float deltaTime)
{
	if (m_IsMovingLeft)
	{
		m_Direction = DIRECTION::LEFT;
		m_Position.x -= MARIO_SPD; // is that true to put it here ?
	}
	else
	{
		m_Direction = DIRECTION::RIGHT;
		m_Position.x += MARIO_SPD; // is that true to put it here ?
	}
}

void Character::Render()
{
	if (m_Direction == DIRECTION::LEFT)
	{
		LOG("x = %f\n", m_Position.x);
		m_Texture->Render(m_Position, SDL_FLIP_HORIZONTAL);
	}
	else
	{
		LOG("x = %f\n", m_Position.x);
		m_Texture->Render(m_Position, SDL_FLIP_NONE);
	} 
}

void Character::Update(float deltaTime, SDL_Event e)
{
	if(m_IsMoving)
		MoveHorizontal(deltaTime);

	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
			// what happend if 2 key press at the same time
		case SDLK_LEFT:
			m_IsMoving = true;
			m_IsMovingLeft = true;
			break;
		case SDLK_RIGHT:
			m_IsMoving = true;
			m_IsMovingLeft = false;
			break;
		}
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_IsMoving = false;
			break;
		case SDLK_RIGHT:
			m_IsMoving = false;
			break;
		}
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
