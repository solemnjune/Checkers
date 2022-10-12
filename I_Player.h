#pragma once
#include <utility>
#include "Interface_functions.h"
class GameFieldLogic;

class I_Player
{
public:
	enum class Side {  white = 0, black};
	I_Player(Side playSide, GameFieldLogic* field) : side(playSide), fieldp(field) {}
	virtual ~I_Player() {}
	void render();
	void renderArrow();
	virtual void NullifyWinsAndCounts();
	void setMiniCheckers(wrapTexture* checkersPiecesMiniTexture, int miniCheckersX, int miniCheckersY);
	void setNumbers(wrapTexture* numbersTexture, int winsCountX, int WinsCountY);
	void setArrow(wrapTexture* buttonsTexture, int arrowX, int arrowY);

	const int getWins() { return wins; }
	int& setWins() { return wins; }
	const int getCheckersKilled() { return checkersKilled; }
	int& setCheckersKilled() { return checkersKilled; }
	const Side getSide() { return side; }

	virtual bool selectSquare() = 0;
	bool checkSideOfSquare(int x, int y);
protected:
	const Side side;
	int wins;
	int checkersKilled;

	SDL_Rect tMiniCheckersRect;
	SDL_Rect tArrowRect;
	SDL_Rect tWinsCountRect;
	SDL_Rect tCheckersCountRect;
	SDL_Rect tMiniCheckersNumber;

	wrapTexture* checkersPiecesMiniTexturep;
	wrapTexture* numbersTexturep;
	wrapTexture* arrowTexturep;

	GameFieldLogic* const fieldp;
	


	
};