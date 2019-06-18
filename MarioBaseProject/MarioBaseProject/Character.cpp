#include "Character.h"
#include "Texture2D.h"
#include "LevelMap.h"

Character::Character()
{
	m_Position = Vector2D();
	m_Renderer = nullptr;
	m_Texture = nullptr;
	m_Direction = DIRECTION::RIGHT;
	m_IsMovingLeft = false;
	m_IsMoving = false;
	m_JumpForce = 0.0f;
	m_CollisionRadius = INITIAL_COLLISION_RAIDUS;
	m_LevelMap = nullptr;
}

Character::Character(SDL_Renderer* renderer, std::string path, Vector2D startPosition, LevelMap* map)
{
	m_Renderer = renderer;
	m_Position = startPosition;
	m_Direction = DIRECTION::RIGHT;
	m_IsMovingLeft = false;
	m_JumpForce = JUMP_FORCE;
	m_CollisionRadius = INITIAL_COLLISION_RAIDUS;
	m_Texture = new Texture2D(renderer);
	m_LevelMap = map;
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

Rect2D Character::GetCollisionBox()
{
	return Rect2D(m_Position.x, m_Position.y, m_Texture->GetWidth(), m_Texture->GetHeight());
}

float Character::GetCollisionRadius()
{
	return m_CollisionRadius;
}

void Character::Jump()
{
	if (!m_IsJumping)
	{
		m_JumpForce = JUMP_FORCE;
		m_IsJumping = true;
		m_CanJump = false;
	}
}

void Character::AddGravity(float deltaTime)
{
	m_Position.y += 96  * deltaTime;
	m_CanJump = false;
}

void Character::MoveHorizontal(float deltaTime)
{
	if (m_IsMovingLeft)
	{
		m_Direction = DIRECTION::LEFT;
		m_Position.x -= (MOVEMENT_SPD * deltaTime); // is that true to put it here ?
	}
	else
	{
		m_Direction = DIRECTION::RIGHT;
		m_Position.x += (MOVEMENT_SPD * deltaTime); // is that true to put it here ?
	}
}

void Character::Render()
{
	if (m_Direction == DIRECTION::LEFT)
	{
		//LOG("x = %f\n", m_Position.x);
		m_Texture->Render(m_Position, SDL_FLIP_HORIZONTAL);
	}
	else
	{
		//LOG("x = %f\n", m_Position.x);
		m_Texture->Render(m_Position, SDL_FLIP_NONE);
	} 
}

void Character::Update(float deltaTime, SDL_Event e)
{
	// Collision position variable
	int centralXPosition = (int)(m_Position.x + (m_Texture->GetWidth() * 0.5f)) / TILE_WIDTH;
	int footPosition = (int)(m_Position.y + (m_Texture->GetHeight())) / TILE_HEIGHT;

	// Deal with gravity
	if (m_LevelMap->GetTileAt(footPosition, centralXPosition) == 0)
	{
		AddGravity(deltaTime);
	}
	else
	{
		m_CanJump = true;
	}

	//if (m_Position.y >= INITIAL_POS_MARIO_Y)
	//{
	//	m_CanJump = true;
	//}
	//else
	//{
	//	m_CanJump = false;
	//	AddGravity(deltaTime);
	//}

	if (m_IsJumping)
	{
		m_Position.y -= m_JumpForce * deltaTime;
		m_JumpForce -= GRAVITY * deltaTime;
		LOG("jump Force = %f", m_JumpForce);
		if (m_JumpForce <= 0.0f)
		{
			m_IsJumping = false;
		}
	}

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
		case SDLK_UP:
			//if(m_CanJump)
				Jump();
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
