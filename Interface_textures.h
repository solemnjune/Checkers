#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

//The window we'll be rendering to
extern SDL_Window* gWindow;

//The window renderer
extern SDL_Renderer* gRenderer ;

//Current displayed texture
extern SDL_Texture* gTexture ;


class wrapTexture
{
public:
	//Initializes variables
	wrapTexture();

	//Deallocates memory
	~wrapTexture();

	//Loads image at specified path
	bool loadFromFile(std::string path, bool whiteBackground = 0);

	//Deallocates texture
	void free();

	//Renders texture at given point
	void virtual render(SDL_Rect * trect);

	const int getWidth() const {
		return sourceRect.w;
	}
	const int getHeight() const {
		return sourceRect.h;
	}
	void setWidth(int Width) {
		sourceRect.w = Width;
	}
	void setHeigth(int Height) {
		sourceRect.h = Height;
	}

	const int getX() const {
		return sourceRect.x;
	}
	const int getY() const {
		return sourceRect.y;
	}
	void setX(int x) {
		sourceRect.x = x;
	}
	void setY(int y) {
		sourceRect.y = y;
	}

	const int getOriginalHeight() {
		return originalHeight;
	}

	const int getOriginalWidth() {
		return originalWidth;
	}

private:
	//The actual hardware texture
	SDL_Texture* myTexture;
	SDL_Rect sourceRect;
	//Image dimensions
	int originalWidth;
	int originalHeight;
};




//Screen dimension constants
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;


