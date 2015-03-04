// could not slow sprite down looks rapid and unnatural

#include <SDL.h>
#include "Sprite.h"
#include <map>
#include <vector>

Sprite::Sprite(int width, int height, SDL_Renderer* ren)
{
	Sprite::width = width;
	Sprite::height = height;
	renderer = ren;
}

void Sprite::setPos(int x, int y)
{
	currX = x;
	currY = y;
}

void Sprite::movex(int delta)
{
	currX += delta;
}
void Sprite::movey(int delta)
{
	currY += delta;
}
int Sprite::getX()
{
	return currX;
}
int Sprite::getY()
{
	return currY;
}

// makeFrame returns the unique index of the frame
int Sprite::makeFrame(SDL_Texture* texture, int x, int y)
{
	Sprite::frame frame;
	frame.texture = texture;
	frame.x = x;
	frame.y = y;
	frames.push_back(frame);
	int frame_index = frames.size() - 1;
	return frame_index;
}

// makeFrame returns the unique index of the frame
int Sprite::makeFrame(SDL_Texture* texture, int x, int y, double rotateDegrees, SDL_RendererFlip flip, int scaleFactor)
{
	Sprite::frame frame;
	frame.texture = texture;
	frame.x = x;
	frame.y = y;
	frame.angle = rotateDegrees;
	frame.flip = flip;
	frame.scaleFactor = scaleFactor;
	frames.push_back(frame);
	int frame_index = frames.size() - 1;
	return frame_index;
}

// addFrameToSequence returns the number of frames in the sequence after the add
int Sprite::addFrameToSequence(std::string seqName, int frameIndex)
{
	int count = 0;
	if (sequenceList.find(seqName) == sequenceList.end())
	{ 
		std::vector<int> newVector;
		newVector.push_back(frameIndex);
		sequenceList.insert(std::pair<std::string, std::vector<int>>(seqName, newVector));
		count = 1;
	}
	else
	{
		sequenceList.at(seqName).push_back(frameIndex);
		count = sequenceList.count(seqName);
	}
		
	return count;
}

// show(int) renders the frame with the specified frameIndex
void Sprite::show(int frameIndex)
{
	SDL_Texture *texture = frames.at(frameIndex).texture;
	
	

	SDL_Rect dst;
	dst.x = Sprite::currX;
	dst.y = Sprite::currY;
	dst.h = Sprite::height;
	dst.w = Sprite::width;

	SDL_Rect clip;
	clip.x = frames.at(frameIndex).x;
	clip.y = frames.at(frameIndex).y;
	clip.h = Sprite::height;
	clip.w = Sprite::width;

	
	SDL_Point* center = NULL;
	SDL_RendererFlip flip = frames.at(frameIndex).flip;
	double angle = frames.at(frameIndex).angle;
	if (frames.at(frameIndex).scaleFactor != 1)
	{
		int newX = frames.at(frameIndex).x * frames.at(frameIndex).scaleFactor;
		int newY = frames.at(frameIndex).y * frames.at(frameIndex).scaleFactor;
		SDL_RenderSetLogicalSize(renderer, 5, newY);
	}
	SDL_RenderCopyEx(renderer, texture, &clip, &dst, angle, center, flip);
}
// show(string) cycles through all frames in the specified sequence, one per call
void Sprite::show(std::string sequence)
{
	if (sequenceIndex >= sequenceList[sequence].size())
	{
		sequenceIndex = 0;
	}
	
	int frame_index = sequenceList[sequence][sequenceIndex];
	show(frame_index);
	++sequenceIndex;
	
}
