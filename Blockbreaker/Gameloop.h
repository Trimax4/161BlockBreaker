#pragma once

#include <sstream>
#include <iostream>
#include "SDL.h"
#include "Entity.h"

class Gameloop
{
public:
	void Run();

private:
	void Initialize(); // Initialize classes
	void Update(); // Update logic and entities
	void Exit();   // Shutdown classes and exit
	void DrawFrame();     // Update and draw the game

	void logSDLError(std::ostream &os, const std::string &msg); // logs SDL errors
	SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren); // loads SDL texture

	bool _running = true;

	// Frame variables
	SDL_Window *window;
	SDL_Renderer *renderer;
	Entity * bg;
	Entity * player;
};