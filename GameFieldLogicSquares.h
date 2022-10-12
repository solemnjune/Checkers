#pragma once

class GameFieldLogic;

class GameFieldLogicSquares
{
public:
	enum class SquareState { Empty = 0, BlackMan, WhiteMan, BlackKing, WhiteKing };
	void init();
	bool move(int rowStart, int colonStart, int rowTarget, int colonTarget);
	const SquareState getState(int x, int y) const
	{
		return state[x][y];
	}
	SquareState& setState(int x, int y)
	{
		return state[x][y];
	}
private:
	SquareState state[8][4];

	
	friend GameFieldLogic;
};