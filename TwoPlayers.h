#pragma once
#include "I_GameStates.h"
#include "Interface_textures.h"
#include "GameFieldLogic.h"
#include "ClickGameButton.h"
#include "StateGameButton.h"

class TwoPlayers : public I_GameStates
{
public:
	enum class Winner { White = 0, Black, Draw};

	TwoPlayers();
	~TwoPlayers();
	virtual bool Init(GameLoop* game);

	virtual void Draw();
	virtual void HandleEvents();
	virtual void Update();
private:
	typedef I_Player::Side PlayerSide;
	GameLoop* gamePtr;
	Winner lastWinner;

	wrapTexture gameScreen;
	wrapTexture checkersPiecesMiniTexture;
	wrapTexture buttonsTexture;
	wrapTexture numbersTexture;

	GameFieldLogic field;
	SDL_Event event;
	int x, y;

	ClickGameButton toMenuButton;
	ClickGameButton endTurnButton;
	ClickGameButton surrenderButton;
	StateGameButton whiteDrawButton;
	StateGameButton blackDrawButton;

	std::unique_ptr<I_Player> whitePlayer;
	std::unique_ptr<I_Player> blackPlayer;
	std::unique_ptr<I_Player>* currentSidep;

	void changeTurnSide();
	void updateCheckersOwned();
	void makeNewGame(bool draw = 0);

	bool victoryScreenShown;

	friend void I_Player::render();
	friend void I_Player::renderArrow();
};