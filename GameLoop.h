#pragma once
#include "MainMenu.h"
#include "TwoPlayers.h"
#include <vector>
#include <memory>


class GameLoop 
{
public:
	typedef std::unique_ptr<I_GameStates> statesptr;
	void Init();
	bool Running() { return gameRunning; }
	void Draw();
	void HandleEvents();
	void Update();
	void PushState(statesptr&& newstate);
	void PopState();
	void ExitGame() { gameRunning = false; }
	enum class StateOfScreen{MainMenu = 0, PlayingVersusPlayer};
	statesptr* const& getPreviousState() { return previousStateptr; }
private:
	statesptr* previousStateptr;
	std::vector <statesptr> states;
	bool gameRunning;
	StateOfScreen screenState;
	std::unique_ptr<I_GameStates> GameState;
};