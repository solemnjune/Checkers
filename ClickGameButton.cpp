#include "ClickGameButton.h"
#include <iostream>

void  ClickGameButton::init(wrapTexture* buttonTexture, int tX, int tY, int sX, int sW)
{
    buttonTexturep = buttonTexture;

    tRect.h = 120;
    tRect.w = 120;
    tRect.x = tX;
    tRect.y = tY;

    setSourceX() = sX;
    setSourceWidth() = sW;
    framesOfSlideShown = 0;
    renderStage = 0;
    pressedState = false;
    
}


void ClickGameButton::render()
{
    if (pressedState)
    {
        if (framesOfSlideShown < getFramesPerSlide())
        {
            framesOfSlideShown++;
        }
        else
        {
            if (renderStage + 1 < getNumStages())
            {
                renderStage++;
            }
            else
            {
                pressedState = false;
            }
            framesOfSlideShown = 0;
        }
    }
    else
    {
        if (renderStage > 0)
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
    }
    buttonTexturep->setWidth(getSourceWidth());
    buttonTexturep->setHeigth(buttonTexturep->getOriginalHeight() / getMaxButtonsInPicture());
    buttonTexturep->setY(renderStage* buttonTexturep->getHeight());//buttonTexture.y инициализируется здесь, т.к. зависит от меняющегося состояния renderStage
    buttonTexturep->setX(getSourceX());
    buttonTexturep->render(&tRect);

    
}