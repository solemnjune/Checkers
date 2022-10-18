#pragma once
#include "I_Button.h"
class StateGameButton :
    public I_Button
{
public:
    StateGameButton(int numOfStages, int numFramesPerSlide, int numMaxButtonsInPicture) :
        I_Button(numOfStages, numFramesPerSlide, numMaxButtonsInPicture) {}
    void init(wrapTexture* buttonTexture, int tX, int tY, int sX = 0, int sW = 0);
    void render();
    const bool getPressedState() { return pressedState; }
    void pressButton();
    bool isMaxStage() { return renderStage + 1 == getNumStages(); }
    void nullifyButton() { renderStage = 0; framesOfSlideShown = 0; pressedState = false; }
    const int getState() { return renderStage; }
private:
    bool pressedState;
};

