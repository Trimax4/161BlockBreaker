#pragma once

#include "SDL.h"
#include <vector>
#include <map>

class Sprite
{
public:
	Sprite(int width, int height, SDL_Renderer* ren);
	~Sprite(void);

	void setPos(int x, int y);
	void movex(int delta);
	void movey(int delta);
	int getX();
	int getY();

	// makeFrame returns the unique index of the frame
	int makeFrame(SDL_Texture* texture, int x, int y);

	///////////////////////////////////////////////////////////edited make frame
	//allows rotation of the sprites single frame
	//give the ability to make a rotation sprite
	//SDL_RendererFlip takes one of 3 commands 	SDL_FLIP_VERTICAL, SDL_FLIP_NONE, SDL_FLIP_HORIZONTAL
	int makeFrame(SDL_Texture* texture, int x, int y, double rotateDegrees, SDL_RendererFlip flip, int scaleFactor);

	// addFrameToSequence returns the number of frames in the sequence after the add
	int addFrameToSequence(std::string seqName, int frameIndex);

	// show(int) renders the frame with the specified frameIndex
	void show(int frameIndex);
	// show(string) cycles through all frames in the specified sequence, one per call
	void show(std::string sequence);
	//set angle for rotation


// The private part of the class is given as a hint or suggestion.
// In homework 3 you can make any modifications you want to the class's innards.
private:
	int width, height;
	int currX, currY;		// the coordinates of the sprite's upper left hand corner relative to the window
	SDL_Renderer* renderer;

	///////////////////////////////////////////////////////////edited frame
	struct frame
	{
		SDL_Texture* texture;
		int x;
		int y;
		double angle = 0.0;
		SDL_RendererFlip flip = SDL_FLIP_NONE;
		int scaleFactor = 1;
	};
	std::vector<frame> frames;

	std::map<std::string, std::vector<int>> sequenceList;
	int sequenceIndex;		// shared by all sequences; it would be better to have
							// one for each sequence


};

