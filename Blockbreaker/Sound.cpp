#include <SDL.h>
#include "Sound.h"
#include <map>
#include <vector>
#include "stdio.h"


Sound::Sound(std::string file, std::string type)
{
	Sound::filename = file;
	Sound::type = type;
	
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
	}
	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}

	if (type.compare("music") == 0)
	{
		 Sound::music = Mix_LoadMUS(file.c_str());
	}
	else if (type.compare("sound") == 0)
	{
		Sound::sound = Mix_LoadWAV(file.c_str());
		std::cout << "sound loaded   -- " << sound << std::endl;
		std::cout << SDL_GetError << std::endl;
	}
	else
	{
		std::cout << "error wrong type" << std::endl;
	}
}

void Sound::playMusic(int channel)
{
	if (Sound::type.compare("music") == 0)
	{
		if (Mix_PlayingMusic() == 0)
		{
			Mix_PlayMusic(music, channel);
		}
		else
		{
			std::cout << "music is playing" << std::endl;
		}
	}
	else
	{
		std::cout << "error wrong type" << std::endl;
	}
}

void Sound::haltMusic()
{
	if (Sound::type.compare("music") == 0)
	{
		Mix_HaltMusic();
	}
	else
	{
		std::cout << "wrong type" << std::endl;
	}
}

void Sound::pauseMusic()
{
	if (Sound::type.compare("music") == 0)
	{
		if (Mix_PausedMusic() == 1)
		{
			std::cout << "already paused" << std::endl;
		}
		else
		{
			Mix_PauseMusic();
		}
	}
	else
	{
		std::cout << "wrong type" << std::endl;
	}
}

void Sound::resumeMusic()
{
	if (Sound::type.compare("music") == 0)
	{
		if (Mix_PausedMusic() == 1)
		{
			Mix_ResumeMusic();
		}
		else
		{
			std::cout << "already playing" << std::endl;
		}
	}
	else
	{
		std::cout << "wrong type" << std::endl;
	}
}

void Sound::playSound(int channel, int number_of_loops)
{
	if (Sound::type.compare("sound") == 0)
	{
		Mix_PlayChannel(channel, sound, number_of_loops);
	}
	else
	{
		std::cout << "error" << std::endl;
	}
}

bool Sound::isMusicNull()
{
	if (music == NULL)
	{
		std::cout << "failed to load sound" << std::endl;
		return true;
	}
	else
	{
		return false;
	}
}

bool Sound::isSoundNull()
{
	if (sound == NULL)
	{
		std::cout << "failed to load sound" << std::endl;
		return true;
	}
	else
	{
		return false;
	}
}

void Sound::freeAndQuit()
{
	if (type.compare("music") == 0)
	{
		Mix_FreeMusic(music);
	}
	else if (type.compare("sound") == 0)
	{
		Mix_FreeChunk(sound);
	}
	else
	{
		std::cout << "wrong type" << std::endl;
	}

	Mix_Quit();
}

