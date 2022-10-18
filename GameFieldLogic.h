#pragma once
#include "Interface_functions.h"
#include "GameFieldLogicSquares.h"
#include "HumanPlayer.h"
#include <memory>
#include "ClickGameButton.h"

class GameFieldLogic
{
public:
	typedef  GameFieldLogicSquares::SquareState square;
	void render();
	bool update(std::unique_ptr<I_Player>& currentSidep);
	bool init();
	void handleEvents(int x,int y);
	const int getFieldRectX() const
	{
		return fieldRectT.x;
	}
	const int getFieldRectY() const
	{
		return fieldRectT.y;

	}
	const int getFieldRectH() const
	{
		return fieldRectT.h;

	}
	const int getFieldRectW() const
	{
		return fieldRectT.w;

	}
	const int getNumPosMoves() const { return numPossibleMoves; }
	int& setNumPosMoves() { return numPossibleMoves; }
	std::pair<int, int>* setArrPosMoves()
	{
		return possibleMoves;
	}
	std::pair<int, int> const* getArrPosMoves()
	{
		return possibleMoves;
	}
	void nullifySpecialSquares();
	const square getSquareState(int y, int x)
	{
		return fieldLogic.getState(y, x);
	}

	const std::pair<int, int> getSelectedSquare() { return selectedSquare; }
	std::pair<int, int>& setSelectedSquare() { return selectedSquare; }
	const std::pair<int, int> getTargetSquare() { return targetSquare; }
	std::pair<int, int>& setTargetSquare() { return targetSquare; }

	const int getMouseX() { return mouseX; }
	const int getMouseY() { return mouseY; }
	void nullifyMouse() { mouseX = mouseY = -1; }

	const bool getKillMode() { return killMode; }
	void nullifyKillMode() { killMode = false; }

	void checkMoves(std::unique_ptr<I_Player>& currentSidep, bool onlyKills = 0);
	bool checkMovePermition(int x, int y);
	const int getNumManMoves()
	{
		return numMandatoryMoves;
	}

	bool checkAbilityToMove(std::unique_ptr<I_Player>& currentSidep);
	void makeNewGame();
	void checkMandatoryMoves(std::unique_ptr<I_Player>& currentSidep);
	
	bool mouseOnField(int x, int y);
private:
	typedef I_Player::Side PlayerSide;

	bool killMode;
	

	wrapTexture fieldTexture;
	wrapTexture fieldEdgingTexture;
	wrapTexture checkersPiecesTexture;


	
	SDL_Rect fieldRectT;
	SDL_Rect fieldEdgingRectT;
	SDL_Rect squareRects[8][4]; // квадраты, куда будут рендериться картинки шашек

	GameFieldLogicSquares fieldLogic;

	std::pair<int, int> selectedSquare;
	std::pair<int, int> targetSquare;
	std::pair<int, int> possibleMoves[13];
	std::pair<int, int> mandatoryMoves[12];

	//bool killedOne; // следит, чтобы игрок мог закончить ход с помощью кнопки endTurn только если он срубил хотя бы одну шашку

	int numPossibleMoves;
	int numMandatoryMoves;
	int mouseX, mouseY;

	void updateCheckersOwned();
	//void changeTurnSide(std::unique_ptr<I_Player>& currentSidep);

	bool isNotOutOfBounds(int row, int colon);
	bool areOpposite(int row, int colon);

	void checkUpRightMove(int row, int colon, bool killMove = 0, bool lastLayer = 0);
	void checkUpLeftMove(int row, int colon, bool killMove = 0, bool lastLayer = 0);
	void checkDownRightMove(int row, int colon, bool killMove = 0, bool lastLayer = 0);
	void checkDownLeftMove(int row, int colon, bool killMove = 0, bool lastLayer = 0);

	bool move(std::unique_ptr<I_Player>& currentSidep);
	
	void highlightSpecialSquares(); // рендерит специальную текстуру для выделенных и возможных для хода квадратов

	friend void I_Player::render();
	friend void I_Player::renderArrow();

};

