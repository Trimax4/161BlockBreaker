#ifndef CONTROLS_H
#define CONTROLS_H

#include "SDL.h"

class Controls{
public:
	Controls();
	~Controls();

	bool isKeyDown();
	bool checkForKey(SDL_Keycode key);
	bool isMouseDown();
	bool isMouseUp();

	SDL_Keycode getKeyDown();
	int getMousePosX();
	int getMousePosY();

private:
	SDL_Event e;
};

#endif