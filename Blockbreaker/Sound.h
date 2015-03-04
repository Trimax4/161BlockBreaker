#pragma once

#include "SDL.h"
#include "SDL_mixer.h"
#include "string"
#include "vector"
#include "iostream"

class Sound
{
public:
	//for file put this "folder/nameofwavfile"
	// the type is either "sound" or "music"
	Sound(std::string file, std::string type);
	~Sound(void);


	//channel is normally set to -1
	void playMusic(int channel);
	void haltMusic();
	void pauseMusic();
	void resumeMusic();
	bool isMusicNull();
	
	//channel is normally set to -1
	// numbr of loops will play the sound a total number of times over again
	void playSound(int channel, int number_of_loops);
	bool isSoundNull();

	//frees all sounds fromt eh player and quits it place it near SDL_QUIT
	// at the end of the game loop/exit of loop
	void freeAndQuit();
private:
	std::string filename;
	std::string type;
	Mix_Music *music = NULL;
	Mix_Chunk *sound = NULL;
};