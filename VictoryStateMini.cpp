#include "VictoryStateMini.h"
#include "GameLoop.h"
#include <iostream>

VictoryStateMini::VictoryStateMini(int winner)
{
	winnerSide = winner;
}

bool VictoryStateMini::Init(GameLoop* game)
{
	if (!victoryScreen.loadFromFile("PlayingGame/WinScreen.png"))
	{
		return false;
	}
	gamePtr = game;
	playingState = gamePtr->getPreviousState();

	victoryScreen.setHeigth(victoryScreen.getOriginalHeight() / 3);
	victoryScreen.setY(victoryScreen.getOriginalHeight() / 3 * winnerSide);
	
	return true;
}

void VictoryStateMini::Draw()
{
	

	playingState->get()->Draw();
	victoryScreen.render(nullptr);

}

void VictoryStateMini::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
		case SDL_QUIT:
			gamePtr->ExitGame();
			break;
		case SDL_KEYDOWN:
			gamePtr->PopState();
			break;
		case SDL_MOUSEBUTTONDOWN:
			gamePtr->PopState();
			break;
		default:
			break;
		}
	}
}

void VictoryStateMini::Update()
{

}