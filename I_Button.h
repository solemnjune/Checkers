#pragma once
#include "Interface_textures.h"

class wrapTexture;

class I_Button
{
public:
	I_Button(int numOfStages, int numFramesPerSlide, int numMaxButtonsInPicture);
	virtual ~I_Button() {};
	virtual void render() = 0;
	virtual void init(wrapTexture* buttonTexture, int tX, int tY, int sX = 0, int sW = 0) = 0;

	const int getSourceX() { return sourceX; }
	const int getSourceWidth() { return sourceWidth; }
	const int getNumStages(){ return numStages; }
	const int getFramesPerSlide () { return framesPerSlide; }
	const int getMaxButtonsInPicture() { return maxButtonsInPicture; }
	const int getXTrect() { return tRect.x; }
	const int getYTrect() { return tRect.y; }
	const int getHTrect() { return tRect.h; }
	const int getWTrect() { return tRect.w; }
	bool mouseOnButton(int x, int y);
protected:
	wrapTexture* buttonTexturep;
	SDL_Rect tRect;
	int renderStage;
	int framesOfSlideShown;
	int& setSourceX() { return sourceX; }
	int& setSourceWidth() { return sourceWidth; }

private:
	int sourceWidth;
	int sourceX;
	const int numStages;//сколько всего спрайтов кнопки есть в текстуре
	const int framesPerSlide;
	const int maxButtonsInPicture; // сколько спрайтов кнопки может поместиться в текстуру вертикально
};

