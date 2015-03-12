#include <Windows.h>
#include <time.h>
#include "SDL_image.h"

#include "Controls.h"
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


Uint32 renderCallBack(Uint32 interval, void* param)
{
	Gameloop* game = (Gameloop*)param;
	for (Entity* block : game->blocks)
	{
		if (block != nullptr)
			block->move(0, 1);
	}
	game->blocksAnimated = true;
	return 0;
}


Uint32 ballCallBack(Uint32 interval, void* param)
{
	Gameloop* game = (Gameloop*)param;
	game->ball.ball_entity->move(game->ball.x_direction*game->ball.ball_speed, game->ball.y_direction*game->ball.ball_speed);
	game->ballAnimated = true;
	return 0;
}

void Gameloop::Run()
{
	Initialize();
	int past = SDL_GetTicks();
	int now = past, pastfps = past;
	SDL_TimerID timerId = SDL_AddTimer(500, renderCallBack, this);
	SDL_TimerID ballTimer = SDL_AddTimer(20, ballCallBack, this);

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
		if (blocksAnimated)
		{
			blocksAnimated = false;
			SDL_RemoveTimer(timerId);
			timerId = SDL_AddTimer(500, renderCallBack, this);
		}
		if (ballAnimated)
		{
			ballAnimated = false;
			SDL_RemoveTimer(ballTimer);
			ballTimer = SDL_AddTimer(20, ballCallBack, this);
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
	all_entities.push_back(player);

	ball.ball_entity = new Entity(renderer);
	if (!ball.ball_entity->load(resPath + "Ball.png", 20, 20))
	{
		logSDLError(std::cout, "LoadTexture");
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		_running = false;
		return;
	}
	ball.ball_entity->setPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	ball.ball_physics = new Physic(ball.ball_entity);

	left_border = new Entity(renderer);
	if (!left_border->load(resPath + "Block - white.PNG", 10, SCREEN_HEIGHT + 20))
	{
		logSDLError(std::cout, "LoadTexture");
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		_running = false;
		return;
	}
	all_entities.push_back(left_border);

	right_border = new Entity(renderer);
	if (!right_border->load(resPath + "Block - white.PNG", 10, SCREEN_HEIGHT + 20))
	{
		logSDLError(std::cout, "LoadTexture");
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		_running = false;
		return;
	}
	right_border->move(SCREEN_WIDTH - 10, 0);
	all_entities.push_back(right_border);

	top_border = new Entity(renderer);
	if (!top_border->load(resPath + "Block - white.PNG", SCREEN_WIDTH, 10))
	{
		logSDLError(std::cout, "LoadTexture");
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		_running = false;
		return;
	}
	all_entities.push_back(top_border);

	bottom_border = new Entity(renderer);
	if (!bottom_border->load(resPath + "Block - white.PNG", SCREEN_WIDTH, 10))
	{
		logSDLError(std::cout, "LoadTexture");
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		_running = false;
		return;
	}
	bottom_border->move(0, SCREEN_HEIGHT + 25);
	all_entities.push_back(bottom_border);


	int num_columns = 6;
	int num_rows = 10;
	for (int row = 0; row < num_rows; row++)
	{
		for (int column = 0; column < 6; column++)
		{
			Entity* block = new Entity(renderer);
			blocks.push_back(block);
			all_entities.push_back(block);
		}
	}
	int startY = SCREEN_HEIGHT / 4;
	int startX = 15;
	for (Entity* test_block : blocks)
	{
		if (!test_block->load(resPath + "Block - white.PNG", 100, 30))
		{
			logSDLError(std::cout, "LoadTexture");
			SDL_DestroyWindow(window);
			SDL_DestroyRenderer(renderer);
			SDL_Quit();
			_running = false;
			return;
		}
		test_block->setPos(startX, startY);
		startY += startX == 515 ? -30 : 0;
		startX += startX == 515 ? -500 : 100;
	}



	//}

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

	std::string soundPath = getResourcePath("sound");
	std::string musicPath = getResourcePath("music");
	//std::cout << (soundPath + "wallBounce.wav");
	upSound = new Sound(soundPath + "wallBounce.wav", "sound");
	music = new Sound(musicPath + "Theme.wav", "music");

	//player->setPos(50, 50);
	std::cout << "Initializing complete." << std::endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Update the game logic
void Gameloop::Update()
{

	int time = 0;
	Controls controls;

	if (music->isMusicNull() == false)
	{
		//music->playMusic(-1);
	}
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT){
			EventDispatcher::Get()->SendEvent(E_QUIT);
		}
		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_RIGHT)
			{
				player->move(20, 0);
				//paddle->move(10, 0);
			}
			else if (e.key.keysym.sym == SDLK_LEFT)
			{
				player->move(-20, 0);
				//paddle->move(-10,0);
			}
			else if (e.key.keysym.sym == SDLK_UP)
			{
				//player->move(0, -5);
			}
			else if (e.key.keysym.sym == SDLK_DOWN)
			{
				//player->move(0, 5);
			}
			else if (e.key.keysym.sym == SDLK_q)
			{
				EventDispatcher::Get()->SendEvent(E_ESC_MENU);
			}
			else if (e.key.keysym.sym == SDLK_e)
			{
				EventDispatcher::Get()->SendEvent(E_SUBMENU);
			}
			else if (e.key.keysym.sym == SDLK_w)
			{
				EventDispatcher::Get()->SendEvent(E_RESUME_BUTTON);
			}
		}
	}
	if (ball.ball_entity->getX() < 0)
	{
		ball.x_direction *= -1;
	}
	if (ball.ball_entity->getX() > SCREEN_WIDTH)
	{
		ball.x_direction *= -1;
	}

	if (ball.ball_entity->getY() < 0)
	{
		ball.y_direction *= -1;
	}

	if (ball.ball_entity->getY() > SCREEN_HEIGHT)
	{
		ball.y_direction *= -1;
		//_running = false;
		//Exit();
	}


	int collision = ball.ball_physics->getCircleCollision(all_entities, ball.ball_entity->getX() + (ball.x_direction * ball.ball_speed), ball.ball_entity->getY() + (ball.y_direction * ball.ball_speed));

	if (collision != -1)
	{
		if (collision == 0)
		{
			// ball hit the paddle
			//ball.x_direction *= -1;
			ball.y_direction *= -1;
		}

		else if (collision == 1 || collision == 2)
		{
			// ball hit sides
			ball.x_direction *= -1;
		}
		else if (collision == 3)
		{
			// ball hit the top
			ball.y_direction *= -1;
		}
		else if (collision == 4)
		{
			// ball went through bottom
			//_running = false;
			ball.y_direction *= -1;
		}
		else
		{
			if (upSound->isSoundNull() == false)
			{
				upSound->playSound(-1, 0);
			}
			std::cout << "Y: " << all_entities[collision]->getY() + all_entities[collision]->getH() << std::endl;
			std::cout << ball.ball_entity->getY() << std::endl;
			std::cout << "Just Y: " << all_entities[collision]->getY() << std::endl;
			if (ball.ball_physics->hitBrickBottom(all_entities[collision]->getY() + all_entities[collision]->getH(),
				ball.ball_entity->getY()))
			{
				std::cout << "hit the bottom of brick" << std::endl;
				ball.y_direction *= -1;
			}
			else if (ball.ball_physics->hitBrickTop(all_entities[collision]->getY(),
				ball.ball_entity->getY()))
			{
				std::cout << "hit the top of brick" << std::endl;
				ball.y_direction *= -1;
			}
			else
			{
				std::cout << "hit the side of brick" << std::endl;
				ball.x_direction *= -1;
			}
			delete all_entities[collision];
			all_entities[collision] = nullptr;
			blocks[collision - 5] = nullptr;
			//ball.x_direction *= -1;
			//ball.y_direction *= -1;

		}
	}


	//for (Entity* block : blocks)
	//{
	//	if (time == 0)
	//		block->move(0, 1);
	//}
	//time += 1;

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
	ball.ball_entity->render();
	//left_border->render();
	//right_border->render();
	//top_border->render();
	//bottom_border->render();
	for (Entity* block : blocks)
	{
		if (block != nullptr)
			block->render();
	}
	ui->renderGUI();
	SDL_RenderPresent(renderer);
}

// Exit the game after shutting down classes and cleaning up resources
void Gameloop::Exit()
{
	std::cout << "Exiting game." << std::endl;
	music->freeAndQuit();
	upSound->freeAndQuit();
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