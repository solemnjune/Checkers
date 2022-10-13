#include "StateGameButton.h"


void StateGameButton::init(wrapTexture* buttonTexture, int tX, int tY, int sX, int sW)
{
	buttonTexturep = buttonTexture;

	tRect.h = 50; 
	tRect.w = 211; 
	tRect.x = tX;
	tRect.y = tY;

	setSourceX() = sX;
	setSourceWidth() = sW;
	framesOfSlideShown = 0;
	renderStage = 0;
	pressedState = false;
}

void StateGameButton::pressButton()
{
	if (pressedState)
	{
		pressedState = false;
	}
	else
	{
		pressedState = true;
	}
}
void StateGameButton::render()
{

	if (pressedState && renderStage + 1 < getNumStages())
	{
		if (framesOfSlideShown < getFramesPerSlide())
		{
			framesOfSlideShown++;
		}
		else
		{

			renderStage++;
			framesOfSlideShown = 0;
		}
	}
	else if (!pressedState && renderStage > 0)
	{
		if (framesOfSlideShown < getFramesPerSlide())
		{
			framesOfSlideShown++;
		}
		else
		{
			renderStage--;
			framesOfSlideShown = 0;
		}

	}
	buttonTexturep->setWidth(getSourceWidth());
	buttonTexturep->setHeigth(buttonTexturep->getOriginalHeight() / getMaxButtonsInPicture());
	buttonTexturep->setY(renderStage * buttonTexturep->getHeight());//buttonTexture.y инициализируется здесь, т.к. зависит от меняющегося состояния renderStage
	buttonTexturep->setX(getSourceX());
	buttonTexturep->render(&tRect);
}