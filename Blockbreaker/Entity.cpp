#include <iostream>

#include "Entity.h"

std::vector<Entity*> Entity::EntityList;

Entity::Entity(SDL_Renderer *renderer)
{
	this->renderer = renderer;
	texture = nullptr;
	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;
	EntityList.push_back(this);
}

Entity::~Entity()
{
	//Possibly unnecessary
	SDL_DestroyTexture(texture);
}

bool Entity::load(std::string fileName, int w, int h)
{
	//Currently only allows a single texture to be assigned
	//Either let game programmer overwrite texture or create a new Entity entirely
	if (texture == nullptr)
	{
		if ((texture = IMG_LoadTexture(renderer, fileName.c_str())) == nullptr)
		{
			std::cout << "Warning: " << SDL_GetError() << std::endl;
		}
	}
	rect.w = w;
	rect.h = h;

	return true;
}

void Entity::render()
{
	if (texture)
		SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void Entity::move(int x, int y)
{
	rect.x += x;
	rect.y += y;
}

void Entity::setPos(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

int Entity::getX()
{
	return rect.x;
}
int Entity::getY()
{
	return rect.y;
}
int Entity::getW()
{
	return rect.w;
}
int Entity::getH()
{
	return rect.h;
}

void Entity::onCleanup()
{
	for (auto it = EntityList.begin(); it != EntityList.end(); it++)
	{
		if (*it == this)
		{
			EntityList.erase(it);
			break;
		}
	}
}