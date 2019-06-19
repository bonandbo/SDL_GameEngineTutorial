#pragma once

#include "SDL.h"
#include <iostream>
#include "Commons.h"

class Texture2D;
class LevelMap;

class Character
{
public:
	Character();
	//Character(SDL_Renderer* renderer, std::string path, Vector2D startPosition);
	Character(SDL_Renderer* renderer, std::string path, Vector2D startPosition, LevelMap* map);
	~Character();

	//void Render();
	virtual void Render(); // why not virtual now
	virtual void Update(float deltaTime, SDL_Event e);
	virtual void MoveHorizontal(float deltaTime);

	void		SetPosition(Vector2D pos);
	Vector2D	GetPosition();
	void		AddGravity(float deltaTime, float gravity = 96.0f);
	void		Jump();
	float		GetCollisionRadius();
	Rect2D		GetCollisionBox();
	bool		IsJumping() { return m_IsJumping; };
	void		CancelJump(float deltaTime);

public: // change to public because some of theme was acees from SceneLevel1. To fix later
	SDL_Renderer*	m_Renderer;
	float			m_JumpForce;
	bool			m_IsJumping;
	bool			m_CanJump;
	LevelMap*		m_LevelMap;
	 
public: // change to public because some of theme was acees from SceneLevel1. To fix later
	float			m_CollisionRadius;
	bool			m_IsMovingLeft;
	bool			m_IsMoving;
	DIRECTION		m_Direction;
	Vector2D		m_Position;
	Texture2D*		m_Texture;
};
