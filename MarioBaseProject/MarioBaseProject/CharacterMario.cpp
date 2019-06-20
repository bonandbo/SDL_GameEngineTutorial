#include "CharacterMario.h"
#include "Texture2D.h"
#include "Constants.h"
#include "LevelMap.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, std::string path, Vector2D position, LevelMap* map) 
	: Character(renderer, path, position, map)
{
	
}

CharacterMario::~CharacterMario()
{
	
}

void CharacterMario::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);
	HandleEvent(e);
}

void CharacterMario::HandleEvent(SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_IsMoving = true;
			m_IsMovingLeft = true;
			break;
		case SDLK_RIGHT:
			m_IsMoving = true;
			m_IsMovingLeft = false;
			break;
		default: 
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
			Character::Jump();
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}