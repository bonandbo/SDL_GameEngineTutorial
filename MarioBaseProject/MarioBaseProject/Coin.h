#pragma once

#include <SDL.h>
#include <iostream>

#include "Commons.h"

class Texture2D;
class LevelMap;


class Coin
{
public:
	Coin(SDL_Renderer* renderer, std::string path, Vector2D pos, LevelMap* map);
	~Coin();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void AddGravity(float deltaTime, float gravity);
	void MoveHorizontal(float deltaTime, float momevementSpd);

	void SetSpriteClip();

	Vector2D GetPosition() { return m_Position; };
	float GetWidth() { return m_ASpriteWidth; };
	float GetHeight() { return m_ASpriteHeight; };
	bool GetIsAlive() { return m_isAlive; };

	void SetIsAlive(bool isAlive) { m_isAlive = isAlive; };
	void SetPosition(Vector2D pos) { m_Position = pos; };
	float GetCollisionRadius() { return 10.0f; };

private:
	Texture2D* m_Texture;
	Vector2D m_Position;
	float m_ASpriteWidth;
	float m_ASpriteHeight;
	SDL_Renderer* m_Renderer;
	LevelMap* m_Map;
	bool m_isMovingLeft;
	int m_Frame;
	SDL_Rect m_SpriteClip[NUMBER_COIN_FRAME];
	bool m_isAlive;
};
