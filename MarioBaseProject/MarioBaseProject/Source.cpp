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
bool Update();


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
		switch (e.key.keysym.sym)
		{
			// quit also
		case SDLK_q:
			success = true;
			break;
			// just for prepare
		case SDLK_UP:
			break;
		case SDLK_DOWN:
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
			quit = Update();
		}
	}

	// Close Window and free resource
	CloseSDL();

	return 0;
}