#include "GameLoop.h"
#include <iostream>
void GameLoop::Init()
{
	gameRunning = true;
	screenState = StateOfScreen::MainMenu;
	PushState(std::make_unique<MainMenu>());
	previousStateptr = nullptr;
}



void GameLoop::PushState(statesptr && newstate)
{
	
	
	states.push_back(std::move(newstate));
	previousStateptr = &states.end()[-2];
	if (!states.back()->Init(this))
	{
		std::cerr << "State init error has occured! Closing game...";
		gameRunning = false;
	}
}

void GameLoop::PopState()
{
	if (!states.empty()) {
		states.pop_back();
		previousStateptr = nullptr;
	}

}


void GameLoop::Draw()
{
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);

	states.back()->Draw();
	SDL_RenderPresent(gRenderer);

}
void GameLoop::HandleEvents()
{
	states.back()->HandleEvents();

}
void GameLoop::Update()
{
	states.back()->Update();
}