#pragma once
#include "I_GameStates.h"
#include "Interface_functions.h"
#include <memory>

class VictoryStateMini :
    public I_GameStates
{
public:
	VictoryStateMini(int winner);

	bool Init(GameLoop* game);

	void Draw();
	void HandleEvents();
	void Update();
private:
	wrapTexture victoryScreen;
	std::unique_ptr<I_GameStates>* playingState;
	GameLoop* gamePtr;
	int winnerSide;

};

