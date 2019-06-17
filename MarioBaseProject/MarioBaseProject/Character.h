#pragma once

#include "SDL.h"
#include <iostream>
#include "Commons.h"

class Texture2D;

class Character
{
public:
	Character();
	Character(SDL_Renderer* renderer, std::string path, Vector2D startPosition);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	virtual void MoveHorizontal(float deltaTime);

	void SetPosition(Vector2D pos);
	Vector2D GetPosition();
	void AddGravity(float deltaTime);
	void Jump();
private:
	SDL_Renderer* m_Renderer;
	Vector2D m_Position;
	Texture2D* m_Texture;
	DIRECTION m_Direction;
	bool m_IsMovingLeft;
	bool m_IsMoving;
	float m_JumpForce;
	bool m_IsJumping;
	bool m_CanJump;
};
