#include <windows.h>
#include <time.h>
#include "SDL_image.h"
#pragma comment(lib,"user32.lib") 
#pragma comment(lib,"winmm.lib")

//#include "Controls.h"
#include "EventDispatcher.h"
#include "res_path.h"
#include "Gameloop.h"

#define PI 3.14159256

const int UPDATE_INTERVAL = 1000 / 60;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int get_num_brick_X(int w)
{
	if (SCREEN_WIDTH / w == 0)
		return SCREEN_WIDTH / w - 1;
	return SCREEN_WIDTH / w;
}

void get_bricks(int w, int h, SDL_Renderer *renderer, std::string filePath)
{
	int num_brick_X = get_num_brick_X(w);
	int num_brick_Y = SCREEN_HEIGHT / h / 2 - 2;
	int offset = (SCREEN_WIDTH - (num_brick_X * w)) / (num_brick_X - 1);

	Entity* brick;
	int x = 0, y = 0;
	for (int i = 0; i < num_brick_X; i++)
	{
		for (int j = 0; j < num_brick_Y; j++)
		{
			brick = new Entity(renderer);
			brick->load(filePath, w, h);
			brick->setPos(x, y);
			y += offset + h;
		}
		y = 0;
		x += offset + w;
	}
}

void move_ball(Entity *ball, double angle)
{
	static int velX = -5 * cos(angle * PI / 180.0);
	static int velY = -5 * sin(angle * PI / 180.0);
	ball->move(velX, velY);
	if (ball->getX() < 0)
	{
		//flip a velocity
	}
	else if (ball->getX() > SCREEN_WIDTH)
	{
		//flip a velocity
	}
	if (ball->getY() < 0)
	{
		//flip a velocity
	}
	else if (ball->getY() > SCREEN_HEIGHT)
	{
		//flip a velocity
	}
}

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
		}
		if (now - pastfps >= 1000)
		{
			pastfps = now;
		}
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
		SDL_DestroyWindow(window);
		SDL_Quit();
		_running = false;
		return;
	}

	ui = new UI(renderer);
	if (ui->init() == 1)
	{
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

	player = new Entity(renderer);
	if (!player->load(resPath + "Paddle.png", 125, 20))
	{
		logSDLError(std::cout, "LoadTexture");
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		_running = false;
		return;
	}
	player->setPos(SCREEN_WIDTH / 2 - (125 / 2), SCREEN_HEIGHT - 30);

	//ball = new Entity(renderer);
	//if (!ball->load(resPath + "ball.png", 30, 30))
	//{
	//	logSDLError(std::cout, "LoadBall");
	//	SDL_DestroyWindow(window);
	//	SDL_DestroyRenderer(renderer);
	//	SDL_Quit();
	//	_running = false;
	//	return;
	//}
	//int ball_start_X = (SCREEN_WIDTH / 2) - (ball->getW() / 2);
	//int ball_start_Y = SCREEN_HEIGHT / 2;
	//ball->setPos(ball_start_X, ball_start_Y);

	/*paddle = new Entity(renderer);
	if (!paddle->load(resPath + "paddle.png", 120, 30))
	{
	logSDLError(std::cout, "LoadPaddle");
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	_running = false;
	return;
	}
	int paddle_start_X = (SCREEN_WIDTH / 2) - (paddle->getW() / 2);
	int paddle_start_Y = SCREEN_HEIGHT - 100;
	paddle->setPos(paddle_start_X, paddle_start_Y);*/

	//get_bricks(60, 30, renderer, resPath + "brick.png");
	//srand(time(NULL));

	//std::string soundPath = getResourcePath("sound");
	//std::string musicPath = getResourcePath("music");
	////std::cout << (soundPath + "wallBounce.wav");
	//upSound = new Sound(soundPath + "wallBounce.wav", "sound");
	//music = new Sound(musicPath + "Theme.wav", "music");

	//player->setPos(50, 50);
	std::cout << "Initializing complete." << std::endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Update the game logic
void Gameloop::Update()
{
	//Controls controls;
	// Modify default controls to be left and right arrow keys


	//if (music->isMusicNull() == false)
	//{
	//	music->playMusic(-1);
	//}
	//SDL_Event e;
	//while (SDL_PollEvent(&e))
	//{
	//	if (e.type == SDL_QUIT){
	//		EventDispatcher::Get()->SendEvent(E_QUIT);
	//	}
	//	if (controls.isKeyDown())
	//	{
	//		if (controls.checkForKey(SDLK_RIGHT))
	//		{
	//			player->move(5, 0);
	//			//paddle->move(10, 0);
	//		}
	//		else if (controls.checkForKey(SDLK_LEFT))
	//		{
	//			player->move(-5, 0);
	//			//paddle->move(-10,0);
	//		}
	//		else if (controls.checkForKey(SDLK_UP))
	//		{
	//			player->move(0, -5);
	//		}
	//		else if (controls.checkForKey(SDLK_DOWN))
	//		{
	//			player->move(0, 5);
	//			if (upSound->isSoundNull() == false)
	//			{
	//				upSound->playSound(-1, 0);
	//			}
	//		}
	//		else if (e.key.keysym.sym == SDLK_q)
	//		{
	//			EventDispatcher::Get()->SendEvent(E_ESC_MENU);
	//		}
	//		else if (e.key.keysym.sym == SDLK_e)
	//		{
	//			EventDispatcher::Get()->SendEvent(E_SUBMENU);
	//		}
	//		else if (e.key.keysym.sym == SDLK_w)
	//		{
	//			EventDispatcher::Get()->SendEvent(E_RESUME_BUTTON);
	//		}
	//	}
	//}

	//bg->update();
	//player->update();

	/*double angle = rand() % 360;
	move_ball(ball, angle);*/

	// update events
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Handle events in Gameloop class
void Gameloop::EventHandler(const Event &e)
{
	switch (e.Type)
	{
	case E_QUIT:
		_running = false;
		break;
	}
}


// Draw the frames
void Gameloop::DrawFrame()
{
	SDL_RenderClear(renderer);
	bg->render();
	player->render();
	for (auto it = Entity::EntityList.begin(); it != Entity::EntityList.end(); it++)
		(*it)->render();
	ui->renderGUI();
	SDL_RenderPresent(renderer);
}

// Exit the game after shutting down classes and cleaning up resources
void Gameloop::Exit()
{
	std::cout << "Exiting game." << std::endl;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
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