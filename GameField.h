#pragma once
//#include "GameFieldLogic.h"
//#include <memory>
//
//class GameField
//{
//public:
//	typedef I_Player::Side PlayerSide;
//
//	void render()
//	{
//		gameFieldLogic.render();
//	}
//	void update()
//	{
//		gameFieldLogic.update();
//	}
//	bool init()
//	{
//		gameFieldLogic.init();
//	}
//	void handleEvents(int x, int y) 
//	{
//		gameFieldLogic.handleEvents(x, y);
//	}
//	const int getFieldRectX() const
//	{
//		return gameFieldLogic.getFieldRectX();
//	}
//	const int getFieldRectY() const
//	{
//		return gameFieldLogic.getFieldRectY();
//
//	}
//	const int getFieldRectH() const
//	{
//		return gameFieldLogic.getFieldRectH();
//
//	}
//	const int getFieldRectW() const
//	{
//		return gameFieldLogic.getFieldRectW();
//
//	}
//	const int getNumPosMoves() const { return gameFieldLogic.getNumPosMoves(); }
//	int& setNumPosMoves() { return gameFieldLogic.setNumPosMoves(); }
//	void nullifySpecialSquares()
//	{
//		gameFieldLogic;
//	}
//	const GameFieldLogic::square getSquareState(int y, int x)
//	{
//		return gameFieldLogic.getSquareState(y, x);
//	}
//
//	const std::pair<int, int> getSelectedSquare() { return gameFieldLogic.getSelectedSquare(); }
//	std::pair<int, int>& setSelectedSquare() { return gameFieldLogic.setSelectedSquare(); }
//	const std::pair<int, int> getTargetSquare() { return gameFieldLogic.getTargetSquare(); }
//	std::pair<int, int>& setTargetSquare() { return gameFieldLogic.setTargetSquare(); }
//
//	const int getMouseX() { return gameFieldLogic.getMouseX(); }
//	const int getMouseY() { return gameFieldLogic.getMouseY(); }
//	void nullifyMouse() { gameFieldLogic.nullifyMouse(); }
//
//	bool getKillMode() { return gameFieldLogic.getKillMode(); }
//private:
//	PlayerSide turn;
//	GameFieldLogic gameFieldLogic;
//	GameFieldLogicSquares gameFieldLogicSquare;
//	std::unique_ptr<I_Player> whitePlayer;
//	std::unique_ptr<I_Player> blackPlayer;
//};
//
