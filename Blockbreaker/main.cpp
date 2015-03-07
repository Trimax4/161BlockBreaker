#include <iostream>
#include <sstream>
#include <Windows.h>
#include <SDL.h>
#include "res_path.h"
#include "cleanup.h"
#include "SDL_image.h"
#include "UI.h"

void testFunction()
{
	std::cout << "HIIIII" << std::endl;
}
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

/**
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message to
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/
void logSDLError(std::ostream &os, const std::string &msg){
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
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren){
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == nullptr){
		logSDLError(std::cout, "LoadTexture");
	}
	return texture;
}


int main(int argc, char **argv){

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		std::ostringstream debugMsg;
		debugMsg << "SDL_Init Error: " << SDL_GetError() << std::endl;
		OutputDebugString(debugMsg.str().c_str());
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
		logSDLError(std::cout, "IMG_Init");
		SDL_Quit();
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("UI Demo", 800, 100, SCREEN_WIDTH,
		SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr){
		logSDLError(std::cout, "CreateWindow");
		SDL_Quit();
		return 1;
	}
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr){
		logSDLError(std::cout, "CreateRenderer");
		cleanup(window);
		SDL_Quit();
		return 1;
	}

	const std::string resPath = getResourcePath("UIDemo");

	/*SDL_Texture* idle_button = loadTexture(resPath + "menu_button.png", renderer);
	if (idle_button == nullptr)
	{
	cleanup(idle_button, renderer, window);
	IMG_Quit();
	SDL_Quit();
	return 1;
	}

	SDL_Texture* pushed_button = loadTexture(resPath + "menu_button2.png", renderer);
	if (pushed_button == nullptr)
	{
	cleanup(pushed_button, renderer, window);
	IMG_Quit();
	SDL_Quit();
	return 1;
	}*/
	SDL_Texture* esc_menu = loadTexture(resPath + "menu.png", renderer);
	if (esc_menu == nullptr)
	{
		cleanup(esc_menu, renderer, window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	SDL_Texture* quit_button = loadTexture(resPath + "button_quit.png", renderer);
	if (esc_menu == nullptr)
	{
		cleanup(quit_button, renderer, window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	SDL_Texture* quit_button_pushed = loadTexture(resPath + "button_quit_pushed.png", renderer);
	if (esc_menu == nullptr)
	{
		cleanup(quit_button, renderer, window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	SDL_Texture* resume_button = loadTexture(resPath + "button_resume.png", renderer);
	if (esc_menu == nullptr)
	{
		cleanup(resume_button, renderer, window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	SDL_Texture* resume_button_pushed = loadTexture(resPath + "button_resume_pushed.png", renderer);
	if (esc_menu == nullptr)
	{
		cleanup(resume_button, renderer, window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	SDL_Texture* restart_button = loadTexture(resPath + "button_restart.png", renderer);
	if (esc_menu == nullptr)
	{
		cleanup(restart_button, renderer, window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	SDL_Texture* restart_button_pushed = loadTexture(resPath + "button_restart_pushed.png", renderer);
	if (esc_menu == nullptr)
	{
		cleanup(restart_button, renderer, window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	SDL_Texture* sub_menu = loadTexture(resPath + "menu.png", renderer);
	if (esc_menu == nullptr)
	{
		cleanup(esc_menu, renderer, window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	UI* ui = new UI(renderer);

	int x = SCREEN_WIDTH / 2;
	int y = SCREEN_HEIGHT / 2;


	ui->makeMenu("esc_menu", esc_menu, 220, 45);

	ui->makeButton("quit_button", quit_button, quit_button_pushed, 240, 275);
	ui->makeButton("restart_button", restart_button, restart_button_pushed, 240, 185);
	ui->makeButton("resume_button", resume_button, resume_button_pushed, 240, 95, &testFunction);
	ui->makeMenu("sub_menu", sub_menu, 0, 0);




	SDL_Event e;
	bool flag = false;
	bool submenu_flag = false;
	bool quit = false;
	while (!quit){
		//frames =+ 1;
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT){
				quit = true;
			}
			if (e.type == SDL_KEYDOWN){

				if (e.key.keysym.sym == SDLK_ESCAPE)
					quit = true;
				else if (e.key.keysym.sym == SDLK_q)
				{
					//would be best if we can add something here
					//that can pause the game

					flag = !flag;
					/*else
					{
					ui->toggleButtonClick("resume_button");
					ui->useButton("resume_button");
					}*/
				}
				else if (e.key.keysym.sym == SDLK_w)
				{
					ui->toggleButtonClick("resume_button");
					ui->useButton("resume_button");
				}
				else if (e.key.keysym.sym == SDLK_e)
				{
					submenu_flag = !submenu_flag;
				}
			}
		}
		//Render the scene

		SDL_RenderClear(renderer);
		if (flag == true)
		{
			ui->show("esc_menu");
			ui->show("resume_button");
			ui->show("restart_button");
			ui->show("quit_button");
		}
		if (submenu_flag == true)
		{
			ui->show("sub_menu");
			ui->showText("TEST", resPath + "BLOCKUP.ttf", 50, 35, 20, renderer);

		}
		SDL_RenderPresent(renderer);
	}
	cleanup(esc_menu, quit_button, quit_button_pushed,
		resume_button, resume_button_pushed,
		restart_button, restart_button_pushed, renderer, window);
	//cleanup(background, UIsheet, UIsheet2, UIsheet3, renderer, window);
	IMG_Quit();
	SDL_Quit();

	SDL_Quit();

	return 0;
}
