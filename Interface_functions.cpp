#include "Interface_functions.h"
#include <iostream>

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: \n" << SDL_GetError() << std::endl;
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            std::cerr << "Warning: Linear texture filtering not enabled!" << std::endl;
        }

        //Create window
        gWindow = SDL_CreateWindow("Checkers", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        if (gWindow == nullptr)
        {
            std::cerr << "Window could not be created! SDL_Error: \n" << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == NULL)
            {
                std::cerr << "Renderer could not be created! SDL Error: \n" << SDL_GetError() << std::endl;
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    std::cerr << "SDL_image could not initialize! SDL_image Error: \n" << IMG_GetError() << std::endl;
                    success = false;
                }
            }

        }
    }

    return success;
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