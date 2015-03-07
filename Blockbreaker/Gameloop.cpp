#include <Windows.h>
#include "SDL.h"
#include "SDL_image.h"
#include "cleanup.h"
#include "res_path.h"

#include "Sprite.h"
#include "Entity.h"
#include "Gameloop.h"

const int UPDATE_INTERVAL = 1000 / 60;

void Gameloop::Run()
{
	Initialize();
	int past = SDL_GetTicks();
	int now = past, pastfps = past;

	while (_running)
	{
		int timeElapsed = 0;
		Update();

		timeElapsed = (now = SDL_GetTicks()) - past;
		if (timeElapsed >= UPDATE_INTERVAL)
		{
			past = now;
			DrawFrame();
			//_running = false;
			std::cout << "updating interval" << std::endl;
		}
		if (now - pastfps >= 1000)
		{
			pastfps = now;
		}
		//DrawFrame();
	}
	Exit();
}

//////////////////////////////////////////////////////////////////////////////////////
// Initialize the components before starting the loop
void Gameloop::Initialize()
{
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::ostringstream debugMsg;
		debugMsg << "SDL_Init Error: " << SDL_GetError() << std::endl;
		OutputDebugString(debugMsg.str().c_str());
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		_running = false;
		return;
	}

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		logSDLError(std::cout, "IMG_Init");
		SDL_Quit();
		_running = false;
		return;
	}

	window = SDL_CreateWindow("Block Demo", 800, 100, SCREEN_WIDTH,
		SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr){
		logSDLError(std::cout, "CreateWindow");
		SDL_Quit();
		_running = false;
		return;
	}
	renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr){
		logSDLError(std::cout, "CreateRenderer");
		cleanup(window);
		SDL_Quit();
		_running = false;
		return;
	}

	const std::string resPath = getResourcePath("BlockDemo");

	bg = new Entity(renderer);
	// background is from http://searchpp.com/lord-of-the-rings-locations-middleearth-hd/
	if (!bg->load(resPath + "Background.png", SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		logSDLError(std::cout, "LoadTexture");
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		_running = false;
		return;
	}
	//std::cout << resPath << std::endl;

	player = new Entity(renderer);
	if (!player->load(resPath + "sprite.png", 144, 256))
	{
		logSDLError(std::cout, "LoadTexture");
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		_running = false;
		return;
	}

	player->setPos(50, 50);
	std::cout << "Finished initializing." << std::endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Update the game logic
void Gameloop::Update()
{
	// update inputs-controls -- temporary controls
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT){
			_running = false;
		}
		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_RIGHT)
			{
				player->move(5, 0);
			}
			else if (e.key.keysym.sym == SDLK_LEFT)
			{
				player->move(-5, 0);
			}
			else if (e.key.keysym.sym == SDLK_UP)
			{
				player->move(0, -5);
			}
			else if (e.key.keysym.sym == SDLK_DOWN)
			{
				player->move(0, 5);
			}
		}
	}
	// update GUI
	bg->update();
	player->update();
	// update events
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Draw the frames
void Gameloop::DrawFrame()
{
	SDL_RenderClear(renderer);
	bg->render();
	player->render();
	SDL_RenderPresent(renderer);
}

// Exit the game after shutting down classes and cleaning up resources
void Gameloop::Exit()
{
	std::cout << "Shutting down." << std::endl;
	cleanup(renderer, window);
	IMG_Quit();
	SDL_Quit();
}

/////////////////////////////////////////////////////////////////////////////////////////////
/**
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message to
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/
void Gameloop::logSDLError(std::ostream &os, const std::string &msg)
{
	os << msg << " error: " << SDL_GetError() << std::endl;
	std::ostringstream errMsg;
	errMsg << " error: " << SDL_GetError() << std::endl;
	OutputDebugString(errMsg.str().c_str());
}

/**
* Loads an image into a texture on the rendering device
* @param file The image file to load
* @param ren The renderer to load the texture onto
* @return the loaded texture, or nullptr if something went wrong.
*/
SDL_Texture* Gameloop::loadTexture(const std::string &file, SDL_Renderer *ren)
{
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == nullptr)
	{
		logSDLError(std::cout, "LoadTexture");
	}
	return texture;
}