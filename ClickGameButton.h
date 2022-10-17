#pragma once
#include "I_Button.h"
class ClickGameButton :
    public I_Button
{
public:
    ClickGameButton(int numOfStages, int numFramesPerSlide, int numMaxButtonsInPicture): I_Button(numOfStages, numFramesPerSlide, numMaxButtonsInPicture) {}
    void init(wrapTexture* buttonTexture, int tX, int tY, int sX = 0, int sW = 0);
    void render();
    const bool getPressedState() { return pressedState; }
    void pressButton() { pressedState = true; }
    void nullifyButton() { renderStage = 0; framesOfSlideShown = 0; pressedState = false;}
private:
    bool pressedState;
};

