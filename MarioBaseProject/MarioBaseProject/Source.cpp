#include <iostream>
#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_mixer.h>
#include "Constants.h"
#include "Texture2D.h"
#include "Commons.h"
#include "SceneManager.h"

using namespace std;

// Game Class ( after tutorial 5 ? )

// Globals
SDL_Window* g_Window = nullptr; // the window
SDL_Renderer* g_Renderer = nullptr; // the renderer to draw to screen any textures associated with it
SceneMaganer* g_SceneMgr = nullptr; 
float g_Angle = 0.0f; // angle flip
Uint32 g_OldTime;

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

	// if jump here => all good, return the true 
	return true;
}

void CloseSDL()
{
	// Release the window
	SDL_DestroyWindow(g_Window);
	g_Window = nullptr;

	// destroy the scene mgr
	if (g_SceneMgr)
		delete g_SceneMgr;
	g_SceneMgr = nullptr;

	// Quit SDL subsystem
	IMG_Quit(); // dieptt - Is it nesseessary
	SDL_Quit();
}

bool Update()
{
	bool success = false;
	// new time
	Uint32 newTime = SDL_GetTicks();

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
	}

	g_SceneMgr->Update((float)(newTime - g_OldTime) / 1000.0f, e);

	// set the current time to be the old
	g_OldTime = newTime;

	return success;
}

void Render()
{
	// Clear the screen
	SDL_SetRenderDrawColor(g_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_Renderer);

	g_SceneMgr->Render();

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
		//Set up the scene manager - with level 1 as start
		g_SceneMgr = new SceneMaganer(g_Renderer, SCENES::LEVEL_1);

		g_OldTime = SDL_GetTicks(); // 1 frame time track

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