#pragma once
#include "I_Player.h"
#include "GameFieldLogic.h"
#include <iostream>
#include <exception> 
bool I_Player::checkSideOfSquare(int x, int y)
{
	GameFieldLogic::square squareState = fieldp->getSquareState(x, y);
	if (side == Side::black && (squareState == GameFieldLogic::square::BlackMan || squareState == GameFieldLogic::square::BlackKing))
	{
		return true;
	}
	else if (side == Side::white && (squareState == GameFieldLogic::square::WhiteMan || squareState == GameFieldLogic::square::WhiteKing))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void I_Player::NullifyWinsAndCounts()
{
	wins = 0;
	checkersKilled = 0;

	



}
void I_Player::render()
{


	checkersPiecesMiniTexturep->setY(static_cast<int>(side) * (checkersPiecesMiniTexturep->getOriginalHeight() / 2));
	checkersPiecesMiniTexturep->setWidth((checkersPiecesMiniTexturep->getOriginalWidth() / 12) * checkersKilled);
	tMiniCheckersRect.w = 40 * checkersKilled;
	checkersPiecesMiniTexturep->render(&tMiniCheckersRect);

	numbersTexturep->setY(static_cast<int>(side) * (numbersTexturep->getOriginalHeight() / 2));
	numbersTexturep->setX(numbersTexturep->getOriginalWidth() / 13 * wins);
	numbersTexturep->render(&tWinsCountRect);

	numbersTexturep->setY((numbersTexturep->getOriginalHeight() / 2)- (numbersTexturep->getOriginalHeight() / 2* (static_cast<int>(side))));
	numbersTexturep->setX(numbersTexturep->getOriginalWidth() / 13 * checkersKilled);
	numbersTexturep->render(&tMiniCheckersNumber);

}

void I_Player::renderArrow()
{
	arrowTexturep->setHeigth(arrowTexturep->getOriginalHeight() / 6);
	arrowTexturep->setWidth(arrowTexturep->getOriginalWidth() / 2);
	arrowTexturep->setX(0);
	arrowTexturep->setY((arrowTexturep->getOriginalHeight()) / 6 * 5);
	arrowTexturep->render(&tArrowRect);

}

void I_Player::setMiniCheckers(wrapTexture* checkersPiecesMiniTexture, int miniCheckersX, int miniCheckersY)
{
	checkersPiecesMiniTexturep = checkersPiecesMiniTexture;
	tMiniCheckersRect.x = miniCheckersX;
	tMiniCheckersRect.y = miniCheckersY;
	tMiniCheckersRect.h = 33;

	tMiniCheckersNumber.h = 55;
	tMiniCheckersNumber.w = 55;
	tMiniCheckersNumber.x = tMiniCheckersRect.x - 65;
	tMiniCheckersNumber.y = tMiniCheckersRect.y - 12;

}
void I_Player::setNumbers(wrapTexture* numbersTexture, int winsCountX, int WinsCountY)
{
	numbersTexturep = numbersTexture;
	tWinsCountRect.x = winsCountX;
	tWinsCountRect.y = WinsCountY;
	tWinsCountRect.h = 85;
	tWinsCountRect.w = 85;

}
void I_Player::setArrow(wrapTexture* buttonsTexture, int arrowX, int arrowY)
{
	arrowTexturep = buttonsTexture;
	tArrowRect.x = arrowX;
	tArrowRect.y = arrowY;
	tArrowRect.h = 55;
	tArrowRect.w = 220;
}
