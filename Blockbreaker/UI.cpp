#include "UI.h"
#include <iostream>
#include <string>


/*
Creates a UI object that has frames with
width and height equal to the inputted values
@param width The desired width of each frame
@param height The desired height of each frame
@render The renderer to draw the UI with
@return The UI object
*/
UI::UI(SDL_Renderer* ren)
{
	renderer = ren;
}

UI::~UI()
{
	TTF_CloseFont(font);
}


/*
Set the position of the given element (top-left corner)
@param x The new x position
@param y The new y position
*/
void UI::setPos(std::string element, int x, int y)
{
	if (buttonList.find(element) == buttonList.end())
		return;
	buttonList[element].x = x;
	buttonList[element].y = y;
}


/*
Increment/decrement the x position of the given element by delta
@param delta The amount to increment/decrement x by
*/
void UI::movex(std::string element, int delta)
{
	if (buttonList.find(element) == buttonList.end())
		return;
	buttonList[element].x += delta;
}

/*
Increment/decrement the y position of the given element by delta
@param delta The amount to increment/decrement y by
*/
void UI::movey(std::string element, int delta)
{
	if (buttonList.find(element) == buttonList.end())
		return;
	buttonList[element].y += delta;
}

/*
Get the current x position of the given element
@return Current x position of given element
*/
int UI::getX(std::string element)
{
	if (buttonList.find(element) == buttonList.end())
		return -1;
	return buttonList[element].x;
}

/*
Get the current y position of the UI
@return the current y position of the UI
*/
int UI::getY(std::string element)
{
	if (buttonList.find(element) == buttonList.end())
		return -1;
	return buttonList[element].y;
}

/*
Creates a button for the UI
@param name The name for the button
@param idle_frame The source of the idle button frame
@param push_frame The source of the pushed button frame
@param x The x coordinate of the button's top left corner
@param y The y coordinate of the button's top left corner
*/
void UI::makeButton(std::string name, SDL_Texture* idle_frame, SDL_Texture* push_frame, int x, int y, void(*buttonFunction)())
{
	buttonList[name].x = x;
	buttonList[name].y = y;
	buttonList[name].idle_texture = idle_frame;
	buttonList[name].active_texture = push_frame;
	buttonList[name].angle = 0.0;
	SDL_QueryTexture(idle_frame, NULL, NULL, &buttonList[name].width, &buttonList[name].height);
	buttonList[name].hStretch = 0;
	buttonList[name].wStretch = 0;
	buttonList[name].clickFunction = buttonFunction;

}

void UI::makeMenu(std::string name, SDL_Texture* idle_frame, int x, int y)
{
	buttonList[name].x = x;
	buttonList[name].y = y;
	buttonList[name].idle_texture = idle_frame;
	buttonList[name].angle = 0.0;
	SDL_QueryTexture(idle_frame, NULL, NULL, &buttonList[name].width, &buttonList[name].height);
	buttonList[name].hStretch = 0;
	buttonList[name].wStretch = 0;

}

/*
Renders the specified element
@param frameIndex The element to render
*/
void UI::show(std::string element)
{
	SDL_Texture* frameToShow;
	if (buttonList.find(element) == buttonList.end())
		return;
	if (buttonList[element].isClicked)
	{
		frameToShow = buttonList[element].active_texture;
	}
	else
		frameToShow = buttonList[element].idle_texture;

	SDL_Rect destinationRect;
	destinationRect.x = buttonList[element].x;
	destinationRect.y = buttonList[element].y;
	destinationRect.w = buttonList[element].width + buttonList[element].wStretch;
	destinationRect.h = buttonList[element].height + buttonList[element].hStretch;
	if (destinationRect.w <= 0)
		destinationRect.w = 1;
	if (destinationRect.h <= 0)
		destinationRect.h = 1;
	SDL_RenderCopyEx(renderer, frameToShow, NULL, &destinationRect, buttonList[element].angle, NULL, buttonList[element].flip);
}

/*
Toggles the requested button's click state
*/
void UI::toggleButtonClick(std::string element)
{
	buttonList[element].isClicked = !buttonList[element].isClicked;
}

/*
Use the function of the requested button, if it has been activated, otherwise do nothing
*/
void UI::useButton(std::string element)
{
	if (buttonList[element].isClicked && buttonList[element].clickFunction != nullptr)
	{
		buttonList[element].clickFunction();
	}
}

/*
Sets the rotation of the given element to the given degrees
@param new_angle The angle to set the given element to
*/
void UI::rotate(std::string element, double new_angle)
{
	if (buttonList.find(element) == buttonList.end())
		return;
	double* angle = &buttonList[element].angle;
	*angle = new_angle;
	if (*angle < 0)
	{
		*angle = 360 + *angle;
		while (*angle > 360)
		{
			*angle = *angle - 360;
			return;
		}
	}
	while (*angle > 360)
		*angle = *angle - 360;
}

/*
Horizontally flip the given element
*/
void UI::flip_horizontal(std::string element)
{
	if (buttonList.find(element) == buttonList.end())
		return;
	switch (buttonList[element].flip)
	{
	case SDL_FLIP_NONE:
		//std::cout << "Flipped from none" << std::endl;
		buttonList[element].flip = SDL_FLIP_HORIZONTAL;
		break;
	case SDL_FLIP_HORIZONTAL:
		//std::cout << "Reversed horizontal flip, no vertical" << std::endl;
		buttonList[element].flip = SDL_FLIP_NONE;
		break;
	case SDL_FLIP_VERTICAL:
		//std::cout << "Added horizontal flip to vertical flip" << std::endl;
		buttonList[element].flip = (SDL_RendererFlip)(SDL_FLIP_VERTICAL | SDL_FLIP_HORIZONTAL);
		break;
	case SDL_FLIP_VERTICAL | SDL_FLIP_HORIZONTAL:
		//std::cout << "Removed horizontal flip from vertical flip" << std::endl;
		buttonList[element].flip = SDL_FLIP_VERTICAL;
		break;
	}
}

/*
Horizontally flip the given element
*/
void UI::flip_vertical(std::string element)
{
	if (buttonList.find(element) == buttonList.end())
		return;
	switch (buttonList[element].flip)
	{
	case SDL_FLIP_NONE:
		//std::cout << "Flipped from none" << std::endl;
		buttonList[element].flip = SDL_FLIP_VERTICAL;
		break;
	case SDL_FLIP_VERTICAL:
		//std::cout << "Reversed vertical flip, no horizontal" << std::endl;
		buttonList[element].flip = SDL_FLIP_NONE;
		break;
	case SDL_FLIP_HORIZONTAL:
		//std::cout << "Added vertical flip to horizontal flip" << std::endl;
		buttonList[element].flip = (SDL_RendererFlip)(SDL_FLIP_VERTICAL | SDL_FLIP_HORIZONTAL);
		break;
	case SDL_FLIP_VERTICAL | SDL_FLIP_HORIZONTAL:
		//std::cout << "Removed vertical flip from horizontal flip" << std::endl;
		buttonList[element].flip = SDL_FLIP_HORIZONTAL;
		break;
	}
}

/*
Stretch the height and the width of the given element by the given values
@param wStretch The amount to stretch the given element's width by
@param hStretch The amount to stretch the given element's height by
*/
void UI::stretch(std::string element, int wStretch, int hStretch)
{
	if (buttonList.find(element) == buttonList.end())
		return;
	buttonList[element].hStretch = hStretch;
	buttonList[element].wStretch = wStretch;
}

/*
Stretch the height and width of the given element by the given value
@param stretch The amount to stretch the UI by
*/
void UI::stretch(std::string element, int stretch)
{
	if (buttonList.find(element) == buttonList.end())
		return;
	buttonList[element].hStretch = stretch;
	buttonList[element].wStretch = stretch;
}



/*void UI::showText(std::string text, std::string &fontName, int fontSize, int x, int y, SDL_Renderer* renderer)
{
if (TTF_Init() != 0){
std::cout << "TTF_Init" << std::endl;
SDL_Quit();
return;
}
font = TTF_OpenFont(fontName.c_str(), fontSize);
if (font == nullptr)
{
std::string error = SDL_GetError();
std::cout << error << std::endl;
TTF_CloseFont(font);
return;
}

SDL_Color color = { 0, 0, 0, 0 };

SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
if (textSurface == nullptr)
{
std::cout << "Can't create surface" << std::endl;
return;
}

int text_width = textSurface->w;
int text_height = textSurface->h;


SDL_Rect dst;
dst.x = x;
dst.y = y;
dst.w = text_width;
dst.h = text_height;

SDL_Texture *texture_message = SDL_CreateTextureFromSurface(renderer, textSurface);
if (texture_message == nullptr)
{
std::cout << "Can't create texture" << std::endl;
return;
}

SDL_RenderCopy(renderer, texture_message, NULL, &dst);
SDL_FreeSurface(textSurface);
SDL_DestroyTexture(texture_message);

}*/

SDL_Color UI::selectColor(std::string text_color)
{
	if (text_color == "white" || text_color == "WHITE" || text_color == "White")
	{
		std::cout << "in here" << std::endl;
		SDL_Color color = { 255, 255, 255, 255 };
		return color;
	}
	else if (text_color == "black" || text_color == "BLACK" || text_color == "Black")
	{
		SDL_Color color = { 0, 0, 0, 0 };
		return color;
	}
	else if (text_color == "blue" || text_color == "BLUE" || text_color == "Blue")
	{
		SDL_Color color = { 0, 0, 255, 0 };
		return color;
	}
	else if (text_color == "red" || text_color == "RED" || text_color == "Red")
	{
		SDL_Color color = { 255, 0, 0, 0 };
		return color;
	}
	else if (text_color == "green" || text_color == "GREEN" || text_color == "Green")
	{
		SDL_Color color = { 0, 255, 0, 0 };
		return color;
	}
	else if (text_color == "yellow" || text_color == "YELLOW" || text_color == "Yellow")
	{
		SDL_Color color = { 255, 255, 0, 0 };
		return color;
	}
	else if (text_color == "orange" || text_color == "ORANGE" || text_color == "Orange")
	{
		SDL_Color color = { 255, 128, 0, 0 };
		return color;
	}
	else if (text_color == "cyan" || text_color == "CYAN" || text_color == "Cyan")
	{
		SDL_Color color = { 0, 255, 255, 0 };
		return color;
	}
	else if (text_color == "purple" || text_color == "PURPLE" || text_color == "Purple")
	{
		SDL_Color color = { 127, 0, 255, 0 };
		return color;
	}
	else if (text_color == "gray" || text_color == "GRAY" || text_color == "Gray")
	{
		SDL_Color color = { 128, 128, 128, 0 };
		return color;
	}
	else if (text_color == "pink" || text_color == "PINK" || text_color == "Pink")
	{
		SDL_Color color = { 255, 0, 127, 0 };
		return color;
	}
	else if (text_color == "light green" || text_color == "LIGHT GREEN" || text_color == "Light Green")
	{
		SDL_Color color = { 128, 255, 0, 0 };
		return color;
	}


}

void UI::showText(std::string text, std::string &fontName, int fontSize, int x, int y, SDL_Renderer* renderer, SDL_Color color)
{
	if (TTF_Init() != 0){
		std::cout << "TTF_Init" << std::endl;
		SDL_Quit();
		return;
	}
	font = TTF_OpenFont(fontName.c_str(), fontSize);
	if (font == nullptr)
	{
		std::string error = SDL_GetError();
		std::cout << error << std::endl;
		TTF_CloseFont(font);
		return;
	}

	//SDL_Color color = { 255, 0, 0, 0 };


	SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
	if (textSurface == nullptr)
	{
		std::cout << "Can't create surface" << std::endl;
		return;
	}

	int text_width = textSurface->w;
	int text_height = textSurface->h;


	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = text_width;
	dst.h = text_height;

	SDL_Texture *texture_message = SDL_CreateTextureFromSurface(renderer, textSurface);
	if (texture_message == nullptr)
	{
		std::cout << "Can't create texture" << std::endl;
		return;
	}

	SDL_RenderCopy(renderer, texture_message, NULL, &dst);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(texture_message);

}

