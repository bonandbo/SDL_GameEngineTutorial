#pragma once

#include <SDL.h>
#include <string>
#include "Constants.h"
#include "Commons.h"

class Texture2D
{
public:
	Texture2D();
	Texture2D(SDL_Renderer* renderer);
	~Texture2D();

	bool LoadFromFile(std::string path);
	void Render(Vector2D newPosition, SDL_RendererFlip flip, double angle = 0.0f);
	void Render(SDL_Rect srcRect, SDL_Rect desRect, SDL_RendererFlip flip, double angle = 0.0f);
	void Free();

	size_t GetWidth() { return m_Width; };
	size_t GetHeight() { return m_Height; };

private:
	SDL_Renderer* m_Renderer;
	SDL_Texture* m_Texture;

	size_t m_Width;
	size_t m_Height;
};