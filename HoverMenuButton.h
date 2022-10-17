#pragma once
#include "I_Button.h"

class HoverMenuButton : public I_Button
{
public:
	enum class MenuChoice { twoPlayers = 0, vsCPU, options, exit };
	HoverMenuButton(MenuChoice type, int numOfStages, int numFramesPerSlide, int numMaxButtonsInPicture);
	void init(wrapTexture* buttonTexture, int tX, int tY, int sX = 0, int sW = 0);
	void render();
	static void changeSelectedButtonUp();
	static void changeSelectedButtonDown();
	static const MenuChoice& getSelectedButton();
	static MenuChoice& setSelectedButton();
	


private:
	int framesOfSlideShown; // сколько раз был показан слайд	
	static MenuChoice selectedButton;
	const MenuChoice buttonType;
};



