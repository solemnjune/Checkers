#include "Interface_textures.h"
#include <iostream>

//The window we'll be rendering to
SDL_Window* gWindow = nullptr;


//The window renderer
SDL_Renderer* gRenderer = nullptr;

//Current displayed texture
SDL_Texture* gTexture = nullptr;



wrapTexture::wrapTexture()
{
    //Initialize
    myTexture = nullptr;
    originalHeight = 0;
    originalWidth = 0;
}

wrapTexture::~wrapTexture()
{
    //Deallocate
    free();
}

bool wrapTexture::loadFromFile(std::string path, bool whiteBackground)
{
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture* newTexture = nullptr;
    sourceRect.x = sourceRect.y = 0;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr)
    {
        std::cerr << "Unable to load image ! SDL_image Error: \n" << path.c_str() << ' ' << IMG_GetError()<< std::endl;
    }
    else
    {
        if (whiteBackground == 1) 
        {
            //Color key image
            SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));
        }
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == nullptr)
        {
            std::cerr << "Unable to create texture from %s! SDL Error: \n" << path.c_str() << ' ' << SDL_GetError() << std::endl;
        }
        else
        {
            //Get image dimensions
            
            originalWidth = sourceRect.w = loadedSurface->w;
            originalHeight = sourceRect.h = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    //Return success
    myTexture = newTexture;
    return myTexture != nullptr;
}

void wrapTexture::free()
{
    //Free texture if it exists
    if (myTexture != nullptr)
    {
        SDL_DestroyTexture(myTexture);
        myTexture = nullptr;
        originalHeight = 0;
        originalWidth = 0;
        sourceRect.x = sourceRect.y = sourceRect.w = sourceRect.h = 0;
    }
}

void wrapTexture::render(SDL_Rect* trect)

{
    SDL_RenderCopy(gRenderer, myTexture, &sourceRect, trect);
}

