#pragma once

#include "Commons.h"
#include "SDL.h"

class Texture2D;
class LevelMap;


class PowBlock
{
public:
	PowBlock();
	PowBlock(SDL_Renderer* renderer, LevelMap* map, Vector2D position);
	~PowBlock();

	void Render();
	void Update(float deltaTime);
	Rect2D GetCollision();
	void TakeAHit();
	bool IsAvailable();

private:
	Texture2D* m_Texture;
	SDL_Renderer* m_Renderer;
	LevelMap* m_LevelMap;
	Vector2D m_Position;

	int m_Width;
	int m_Height;

	int m_NumberOfHitsLeft;
};
