#include <iostream>
#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_mixer.h>
#include "Constants.h"

using namespace std;

// Globals
SDL_Window* g_Window = nullptr;

// Function Prototypes
bool InitSDL();
void CloseSDL();

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

	// if jump here => all good, return the true 
	return true;
}

void CloseSDL()
{
	// Release the window
	SDL_DestroyWindow(g_Window);
	g_Window = nullptr;

	// Quit SDL subsystem
	IMG_Quit(); // dieptt - Is it nesseessary
	SDL_Quit();
}

int main(int argc, char* args[])
{
	// Check if SDL was set up correctly
	if (InitSDL())
	{
		// Pause 5 sec
		SDL_Delay(5000);
	}

	// Close Window and free resource
	CloseSDL();

	return 0;
}