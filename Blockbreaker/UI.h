#pragma once

#include "SDL.h"
#include "SDL_ttf.h"
#include <vector>
#include <map>
class UI
{
public:
	UI(SDL_Renderer* ren);
	~UI(void);

	//Creates a button with the given coordinates with an animation between the two given textures
	void makeButton(std::string name, SDL_Texture* idle_frame, SDL_Texture* push_frame, int x, int y);

	void UI::makeMenu(std::string name, SDL_Texture* idle_frame, int x, int y);

	void setPos(std::string element, int x, int y);
	void movex(std::string element, int delta);
	void movey(std::string element, int delta);
	int getX(std::string element);
	int getY(std::string element);

	// show renders the requested element
	void show(std::string element);

	//Set rotation of the requested element by the given degrees
	void rotate(std::string element, double new_angle);

	//Stretch the height and the width of the requested element by the given values (Used for uneven values)
	void stretch(std::string element, int wStretch, int hStretch);

	//Stretch the height and the width of the requested element by the given value (Used for an even scale)
	void stretch(std::string element, int stretch);

	//Horizontally flip the image of the requested element
	void flip_horizontal(std::string element);

	//Vertically flip the image of the requested element
	void flip_vertical(std::string element);

	void showText(std::string text, std::string &fontName, int fontSize, int x, int y, SDL_Renderer* renderer);

	// The private part of the class is given as a hint or suggestion.
	// In homework 3 you can make any modifications you want to the class's innards.
private:
	SDL_Renderer* renderer;
	TTF_Font* font;

	struct button
	{
		SDL_Texture* idle_texture;
		SDL_Texture* active_texture;
		int x, y;							// The coordinates of the button's left hand corner relative to the window
		int width, height;					// The width and height of the button
		double angle;						// The current angle of the button
		int hStretch, wStretch;			// The amount to stretch the button
		SDL_RendererFlip flip;				// Used to flip the button
		//bool isClicked;					// Is the button clicked?
		//function clickFunction			// Function to activate onn a click


	};

	std::map<std::string, button> buttonList;



};

