#pragma once

#include <sstream>
#include <iostream>
#include "SDL.h"
#include "Entity.h"
#include "UI.h"
#include "Sound.h"
#include "Physics.h"

#include "IEventHandler.h"

class Gameloop : public IEventHandler
{
	/* type definition for the "new" timer callback function */
	typedef Uint32(*SDL_NewTimerCallback)(Uint32 interval, void *param);
public:
	void Run();
	std::vector<Entity*> blocks;
	bool blocksAnimated = false;
	bool ballAnimated = false;
	struct game_ball
	{
		Entity* ball_entity;
		Physic* ball_physics;
		int x_direction = 1;
		int y_direction = 1;
		int ball_speed = 5;

	};
	game_ball ball;


private:
	void Initialize(); // Initialize classes
	void Update(); // Update logic and entities
	void Exit();   // Shutdown classes and exit
	void DrawFrame();     // Update and draw the game

	void EventHandler(const Event &e); // Handles Events in the Gameloop class
	void logSDLError(std::ostream &os, const std::string &msg); // logs SDL errors
	SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren); // loads SDL texture
	std::vector<Entity*> all_entities; // All entities except for the ball, paddle is at index 0. 

	bool _running = true;

	// Frame variables
	SDL_Window *window;
	SDL_Renderer *renderer;
	Entity * bg;
	Entity * player;
	Entity* left_border; //Index 1 in all_entities
	Entity* right_border; //Index 2
	Entity* top_border;  //Index 3
	Entity* bottom_border; //Index 4
	//Entity * paddle;
	UI * ui;
	Sound* music, *upSound;
};