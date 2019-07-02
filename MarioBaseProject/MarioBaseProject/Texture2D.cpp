#include "Texture2D.h"
#include <SDL_image.h>

// default constructor
Texture2D::Texture2D()
{
	m_Renderer = nullptr;
	m_Texture = nullptr;
	m_Width = 0;
	m_Height = 0;
}

// non-default constructor
Texture2D::Texture2D(SDL_Renderer* renderer)
{
	m_Renderer = renderer;
	m_Texture = nullptr;
	m_Width = 0;
	m_Height = 0;
}

// destructor
Texture2D::~Texture2D()
{
	Free();
	if (m_Renderer)
	{

		//SDL_DestroyRenderer(m_Renderer); 
		// why can not destroy here ?
		m_Renderer = nullptr;
	}

	m_Width = 0;
	m_Height = 0;
}

bool Texture2D::LoadFromFile(std::string path)
{
	// what happen if we don't make sure the previous not be cleared
	// Free texture only here
	//if (m_Texture)
	//	SDL_DestroyTexture(m_Texture);
	//m_Texture = nullptr;
	
	bool success = false;
	// Load image
	SDL_Surface* p_Surface = IMG_Load(path.c_str());
	if (!p_Surface)
	{
		success = false;
		LOG("Error loading image. E: %s", IMG_GetError());
	}
	else
	{
		// Color the key image - the color to be transparent
		SDL_SetColorKey(p_Surface, SDL_TRUE, SDL_MapRGB(p_Surface->format, 0, 255, 255));

		// Create texture
		m_Texture = SDL_CreateTextureFromSurface(m_Renderer, p_Surface);
		if (!m_Texture)
		{
			success = false;
			LOG("Error create texture from surface. E: %s", SDL_GetError());
		}
		else
		{
			success = true;

			// Set the dimension if the texture can create
			m_Width = p_Surface->w;
			m_Height = p_Surface->h;
		}
	}
	SDL_FreeSurface(p_Surface);

	return success;
}

void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, double angle)
{
	// do we need this ?
	// Clear the screen
	//SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
	//SDL_RenderClear(m_Renderer);

	// Set where to draw Texture
	SDL_Rect renderLocation = { (int)newPosition.x, (int)newPosition.y , (int)m_Width, (int)m_Height };

	// Render it
	SDL_RenderCopyEx(m_Renderer, m_Texture, nullptr, &renderLocation, angle, nullptr, flip);
}

void Texture2D::Render(SDL_Rect srcRect, SDL_Rect desRect, SDL_RendererFlip flip, double angle)
{
	SDL_RenderCopyEx(m_Renderer, m_Texture, &srcRect, &desRect, angle, nullptr, flip);
}

// free texture memory
void Texture2D::Free()
{
	if (m_Texture)
	{
		SDL_DestroyTexture(m_Texture);
		m_Texture = nullptr;
	}
}