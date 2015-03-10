#include "Controls.h"

Controls::Controls() {}

Controls::~Controls() {}

bool Controls::isKeyDown()
{
	if (e.type == SDL_KEYDOWN)
	{
		return true;
	}
	return false;
}

bool Controls::checkForKey(SDL_Keycode key)
{
	if (e.key.keysym.sym == key)
	{
		return true;
	}
	return false;
}

SDL_Keycode Controls::getKeyDown()
{
	return e.key.keysym.sym;
}

bool Controls::isMouseDown()
{
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		return true;
	}
	return false;
}

bool Controls::isMouseUp()
{
	if (e.type == SDL_MOUSEBUTTONUP)
	{
		return true;
	}
	return false;
}

int Controls::getMousePosX()
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	return x;
}

int Controls::getMousePosY()
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	return y;
}