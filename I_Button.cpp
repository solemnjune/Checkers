#include "I_Button.h"


I_Button::I_Button(int numOfStages, int numFramesPerSlide, int numMaxButtonsInPicture):numStages(numOfStages), framesPerSlide(numFramesPerSlide), maxButtonsInPicture(numMaxButtonsInPicture)
{

}
bool I_Button::mouseOnButton(int x, int y)
{
	if (x > tRect.x && x < tRect.x + tRect.w &&
		y > tRect.y && y < tRect.y + tRect.h)
	{
		return true;
	}
	else
	{
		return false;
	}
}