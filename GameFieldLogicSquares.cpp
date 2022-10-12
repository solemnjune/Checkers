#include "GameFieldLogicSquares.h"
#include <iostream>

void GameFieldLogicSquares::init()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			state[i][j] = SquareState::BlackMan;// квадрат шахматного поля чёрный (в шашках фигуры только на чёрном), только тогда, когда сумма номера строки и номера столбца нечётная
		}
	}

	for (int i = 3; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			state[i][j] = SquareState::Empty;
		}
	}

	for (int i = 5; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			state[i][j] = SquareState::WhiteMan;
		}
	}

	


}

bool GameFieldLogicSquares::move(int rowStart, int colonStart, int rowTarget, int colonTarget) {
	if (state[rowStart][colonStart] == SquareState::BlackMan && rowTarget == 7)
	{
		state[rowTarget][colonTarget] = SquareState::BlackKing;
	}
	else if (state[rowStart][colonStart] == SquareState::WhiteMan && rowTarget == 0)
	{
		state[rowTarget][colonTarget] = SquareState::WhiteKing;
	}
	else {
		state[rowTarget][colonTarget] = state[rowStart][colonStart];
	}
	
	int differenceRow = rowTarget - rowStart;
	int differenceColon = colonTarget - colonStart;
	int tempRow = rowStart;
	int tempColon = colonStart;
	int differenceRowSign = rowStart > rowTarget ? -1 : 1;
	int differenceColonSign = colonStart > colonTarget ? -1 : 1;
	bool kill = 0;
	state[tempRow][tempColon] = SquareState::Empty;
	//если игрок срубил шашку, меняем и её состояние на Empty
	while (tempRow != rowTarget)
	{
		if (state[tempRow][tempColon] != SquareState::Empty)
		{
			kill = true;
		}
		state[tempRow][tempColon] = SquareState::Empty;
		
		if (colonStart > colonTarget)
		{
			tempColon = tempColon + (tempRow % 2) * differenceColonSign;
		}
		else
		{
			tempColon = tempColon + ((tempRow + 1) % 2) * differenceColonSign;

		}

		tempRow = rowStart > rowTarget ? tempRow - 1 : tempRow + 1;
		
		
	}
	return kill;
}

