#include <iostream>
#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_mixer.h>
#include "Constants.h"
#include "Texture2D.h"
#include "Commons.h"

using namespace std;

// Game Class ( after tutorial 5 ? )

// Globals
SDL_Window* g_Window = nullptr; // the window
SDL_Renderer* g_Renderer = nullptr; // the renderer to draw to screen any textures associated with it
Texture2D* g_Texture = nullptr; // the texture
float g_Angle = 0.0f; // angle flip

// Function Prototypes
bool InitSDL();
void CloseSDL();
bool Update();
void Render();


// Function declartion

bool InitSDL()
{
	// Init and check if it is OK
	if (SDL_Init(SDL_INIT_VIDEO /*| SDL_INIT_EVERYTHING*/) < 0)
	{
		LOG("SDL did not init. Error: %s", SDL_GetError());
		return false;
	}
	
	// if it's OK ( >=1 ) => all good, create window
	g_Window = SDL_CreateWindow("Game Engine Creation", 
								SDL_WINDOWPOS_UNDEFINED, 
								SDL_WINDOWPOS_UNDEFINED, 
								SCREEN_WIDTH, SCREEN_HEIGHT, 
								SDL_WINDOW_SHOWN);
	/*
	SDL_WINDOW_SHOWN
	SDL_WINDOW_FULLSCREEN
	SDL_WINDOW_FULLSCREEN_DESKTOP
	SDL_WINDOW_OPENGL
	SDL_WINDOW_HIDDEN
	SDL_WINDOW_MAXIMIZED
	...
	*/

	// check if window successfully create
	if (g_Window == nullptr)
	{
		LOG("Window can not create. E: %s", SDL_GetError());
		return false;
	}

	// create the renderer
	g_Renderer = SDL_CreateRenderer(g_Window, -1, SDL_RENDERER_ACCELERATED); 
	/*
	SDL_RENDERER_SOFTWARE		The renderer is a software fallback
	SDL_RENDERER_ACCELERATED		The renderer uses hardware acceleration
	SDL_RENDERER_PRESENTVSYNC		Present is synchronized with the refresh rate
	SDL_RENDERER_TARGETTEXTURE		The renderer supports rendering to texture
	*/
	
	// check if the renderer create successfully
	if (!g_Renderer)
	{
		LOG("Renderer can not create. E: %s", SDL_GetError());
		return false;
	}

	// Init PNG loading
	int imageFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imageFlags) & imageFlags))
	{
		LOG("SDL_Image could not init. E: %s", IMG_GetError());
		return false;
	}

	// Load the texture
	g_Texture = new Texture2D(g_Renderer);
	if (!g_Texture->LoadFromFile("Images/test image.bmp"))
	{
		return false;
	}

	// if jump here => all good, return the true 
	return true;
}

void CloseSDL()
{
	// Release the texture
	if (g_Texture)
		delete g_Texture;
	g_Texture = nullptr;

	// Release the window
	SDL_DestroyWindow(g_Window);
	g_Window = nullptr;

	// Quit SDL subsystem
	IMG_Quit(); // dieptt - Is it nesseessary
	SDL_Quit();
}

bool Update()
{
	bool success = true;
	// Event Handler
	SDL_Event e;

	// Get the events
	SDL_PollEvent( &e ); // passing reference => allow e to be adjusted in the SDL_PollEvent

	// Handle events
	switch ( e.type )
	{
		// Click X to quit
	case SDL_QUIT:
		success = true;
		break;
		// after press button and release
	case SDL_KEYUP:
		success = false;
		switch (e.key.keysym.sym)
		{
			// quit also
		case SDLK_q:
			success = true;
			break;
			// just for prepare
		case SDLK_UP:
			g_Angle += 0.1f;
			break;
		case SDLK_DOWN:
			g_Angle -= 0.1f;
			break;
		case SDLK_LEFT:
			break;
		case SDLK_RIGHT:
			break;
		default:
			break;
		}
		// when press mouse button
	case SDL_MOUSEBUTTONDOWN:
		break;
	default:
		success = false;
		break;
	}

	return success;
}

void Render()
{
	// Clear the screen
	SDL_SetRenderDrawColor(g_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_Renderer);

	// Set where to render texture
	SDL_Rect renderLocation = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	//  Render to screen
	SDL_RendererFlip rFlip = SDL_FLIP_HORIZONTAL;

	// Render texture
	g_Texture->Render(Vector2D(), rFlip, g_Angle);
	//g_Texture->Render(Vector2D(), rFlip);

	// Update the screen
	SDL_RenderPresent(g_Renderer);
}

// Main function

int main(int argc, char* args[])
{
	// Flag to check if user want to quit
	bool quit = false;

	// Check if SDL was set up correctly
	if (InitSDL())
	{
		while (!quit)
		{
			// do render while update
			Render();
			quit = Update();
		}
	}

	// Close Window and free resource
	CloseSDL();

	return 0;
}