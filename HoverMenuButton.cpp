#include "HoverMenuButton.h"
HoverMenuButton::MenuChoice HoverMenuButton::selectedButton;

HoverMenuButton::HoverMenuButton(MenuChoice type, int numOfStages, int numFramesPerSlide, int numMaxButtonsInPicture):buttonType(type), I_Button( numOfStages,  numFramesPerSlide, numMaxButtonsInPicture)
{

}



void HoverMenuButton::init(wrapTexture* buttonTexture, int tX, int tY, int sX, int sW)
{
    buttonTexturep = buttonTexture;

    tRect.h = SCREEN_HEIGHT * 0.14;
    tRect.w = SCREEN_WIDTH * 0.38;
    tRect.x = tX;
    tRect.y = tY;

    setSourceX() = sX;
    setSourceWidth() = sW;
    framesOfSlideShown = 0;
    renderStage = 0;

    buttonTexturep->setX(getSourceX());
    buttonTexturep->setHeigth(buttonTexturep->getOriginalHeight() / getMaxButtonsInPicture());
    if (sW == 0)
    {
        setSourceWidth() = buttonTexturep->getOriginalWidth();
    }
    else
    {
        setSourceWidth() = sW;
    }
}

void HoverMenuButton::render() 
{
    
    buttonTexturep->setWidth(getSourceWidth());
    buttonTexturep->setY(renderStage);//buttonTexture.y инициализируется здесь, т.к. зависит от меняющегося состояния renderStage

    buttonTexturep->render(&tRect);

    if (buttonType == selectedButton)
    {
        if (framesOfSlideShown < getFramesPerSlide())
        {
            framesOfSlideShown++;
        }
        else
        {
            if (renderStage < buttonTexturep->getOriginalHeight() / getMaxButtonsInPicture() * (getNumStages()-1))
            {
                renderStage += (buttonTexturep->getOriginalHeight() / getMaxButtonsInPicture());
            }
            framesOfSlideShown = 0;
        }
    }
    else
    {
        renderStage = 0;
    }
}

void HoverMenuButton::changeSelectedButtonUp()
{
    if (selectedButton == MenuChoice::twoPlayers)
    {
        selectedButton = MenuChoice::exit;
    }
    else
    {
        selectedButton = static_cast<MenuChoice>(static_cast<int>(selectedButton) - 1);

    }
}

void HoverMenuButton::changeSelectedButtonDown()
{
    if (selectedButton == MenuChoice::exit)
    {
        selectedButton = MenuChoice::twoPlayers;
    }
    else
    {
        selectedButton = static_cast<MenuChoice>(static_cast<int>(selectedButton) + 1);
    }
}


const HoverMenuButton::MenuChoice& HoverMenuButton::getSelectedButton() {
    return selectedButton;
}

HoverMenuButton::MenuChoice& HoverMenuButton::setSelectedButton() {
    return selectedButton;
}