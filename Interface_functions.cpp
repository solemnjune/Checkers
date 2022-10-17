#include "Interface_functions.h"
#include <iostream>

bool init()
{

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "SDL could not initialize! SDL_Error: \n" << SDL_GetError() << std::endl;
		return false;
	}


	//Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		std::cerr << "Warning: Linear texture filtering not enabled!" << std::endl;
	}

	//Create window
	SDL_DisplayMode currentDimension;
	SDL_GetCurrentDisplayMode(0, &currentDimension);
	if (currentDimension.w > 1920 || currentDimension.h > 1080)
	{
		gWindow = SDL_CreateWindow("Checkers", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_SHOWN);
		std::cerr << "Without resize: currentDimension.w " << currentDimension.w << " currentDimension.h " << currentDimension.h << std::endl;
	}
	else
	{
		gWindow = SDL_CreateWindow("Checkers", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

		std::cerr << "With resize: currentDimension.w " << currentDimension.w << " currentDimension.h " << currentDimension.h << std::endl;

	}
	if (gWindow == nullptr)
	{
		std::cerr << "Window could not be created! SDL_Error: \n" << SDL_GetError() << std::endl;
		return false;
	}

	//Create renderer for window
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_PRESENTVSYNC);
	if (gRenderer == NULL)
	{
		std::cerr << "Renderer could not be created! SDL Error: \n" << SDL_GetError() << std::endl;
		return false;;
	}

	//Initialize renderer color
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		std::cerr << "SDL_image could not initialize! SDL_image Error: \n" << IMG_GetError() << std::endl;
		return false;
	}




	if (!(currentDimension.w > 1920 || currentDimension.h > 1080))
	{
		SDL_RenderSetLogicalSize(gRenderer, 1920, 1080);
		SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
	return true;
}

bool loadMedia(wrapTexture& wT, std::string path)
{
	//Loading success flag
	bool success = true;

	//Load splash image
	if (!wT.loadFromFile(path.c_str()))
	{
		std::cerr << "Unable to load image ! SDL Error: \n"
			<< path << ' ' << SDL_GetError() << std::endl;
		success = false;
	}

	return success;
}







void close()
{
	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;
	gRenderer = nullptr;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}