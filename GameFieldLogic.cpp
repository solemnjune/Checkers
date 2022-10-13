#include "GameFieldLogic.h"
#include <iostream>
#include <algorithm>

bool GameFieldLogic::init()
{
	if (!(fieldTexture.loadFromFile("PlayingGame/Field.png")
		&& fieldEdgingTexture.loadFromFile("PlayingGame/Edging.png")
		&& checkersPiecesTexture.loadFromFile("PlayingGame/CheckersPieces.png", true)))
	{
		std::cerr << "GameField: Failed to load media!\n";
		return false;
	}

	checkersPiecesTexture.setHeigth(checkersPiecesTexture.getOriginalHeight() / 4);
	checkersPiecesTexture.setWidth(checkersPiecesTexture.getOriginalWidth() / 5);

	fieldRectT.x = 158;
	fieldRectT.y = 145;
	const int difference = fieldRectT.x * 0.455;
	fieldEdgingRectT.x = fieldRectT.x - difference;
	fieldEdgingRectT.y = fieldRectT.y - difference;

	fieldRectT.w = 800;
	fieldRectT.h = 800;

	fieldEdgingRectT.w = fieldRectT.w + difference * 2 - 2;
	fieldEdgingRectT.h = fieldRectT.h + difference * 2;




	// вычисляем координаты квадратов, в которые будут рендериться шашки
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			squareRects[j][i].h = squareRects[j][i].w = fieldRectT.h / 8;
			squareRects[j][i].x = fieldRectT.x + fieldRectT.w / 8 * (i * 2 + ((j + 1) % 2));
			squareRects[j][i].y = fieldRectT.y + fieldRectT.h / 8 * j;
		}
	}



	fieldLogic.init();

	selectedSquare.first = -1;
	selectedSquare.second = -1;
	targetSquare.first = -1;
	targetSquare.second = -1;
	numPossibleMoves = 0;
	numMandatoryMoves = 0;
	//killedOne = 0;
	for (auto& i : possibleMoves)
	{
		i.first = -1;
		i.second = -1;
	}

	nullifyMouse();
	killMode = false;

	return true;
}


void GameFieldLogic::render()
{
	fieldEdgingTexture.render(&fieldEdgingRectT);
	fieldTexture.render(&fieldRectT);
	

	highlightSpecialSquares();
	
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			switch (fieldLogic.getState(j, i))
			{
			case square::Empty:
				checkersPiecesTexture.setX(0);
				break;
			case square::BlackMan:
				checkersPiecesTexture.setX(checkersPiecesTexture.getWidth() * 2);
				checkersPiecesTexture.render(&squareRects[j][i]);
				break;
			case square::WhiteMan:
				checkersPiecesTexture.setX(checkersPiecesTexture.getWidth());
				checkersPiecesTexture.render(&squareRects[j][i]);
				break;
			case square::BlackKing:
				checkersPiecesTexture.setX(checkersPiecesTexture.getWidth() * 4);
				checkersPiecesTexture.render(&squareRects[j][i]);
				break;
			case square::WhiteKing:
				checkersPiecesTexture.setX(checkersPiecesTexture.getWidth() * 3);
				checkersPiecesTexture.render(&squareRects[j][i]);
				break;
			default:
				std::cerr << "Field squares Logic rendering error!" << std::endl;
				EXIT_FAILURE;
				break;
			}
		}
	}
}

bool GameFieldLogic::update(std::unique_ptr<I_Player>& currentSidep)
{
	bool toMove = false;
	bool moveEnded = false;

	toMove = currentSidep->selectSquare();

	checkMoves(currentSidep);
	if (toMove)
	{
		
		moveEnded = move(currentSidep);
	}
	targetSquare.first = -1;
	targetSquare.second = -1;
	return moveEnded;
}
void GameFieldLogic::handleEvents(int x, int y)
{


	mouseX = x;
	mouseY = y;


}

void GameFieldLogic::checkMoves(std::unique_ptr<I_Player>& currentSidep, bool onlyKills)
{
	if (selectedSquare.first >= 0)
	{
		numPossibleMoves = 0;
		if (onlyKills == false)
		{
			checkMoves(currentSidep, true);
		}
		if (numPossibleMoves == 0)
		{
			switch (fieldLogic.getState(selectedSquare.first, selectedSquare.second))
			{
			case square::BlackMan:
				checkUpLeftMove(selectedSquare.first, selectedSquare.second, true);
				checkUpRightMove(selectedSquare.first, selectedSquare.second, true);
				checkDownLeftMove(selectedSquare.first, selectedSquare.second, onlyKills);
				checkDownRightMove(selectedSquare.first, selectedSquare.second, onlyKills);
				break;
			case square::WhiteMan:
				checkUpLeftMove(selectedSquare.first, selectedSquare.second, onlyKills);
				checkUpRightMove(selectedSquare.first, selectedSquare.second, onlyKills);
				checkDownLeftMove(selectedSquare.first, selectedSquare.second, true);
				checkDownRightMove(selectedSquare.first, selectedSquare.second, true);
				break;
			case square::BlackKing:
				checkDownLeftMove(selectedSquare.first, selectedSquare.second, onlyKills);
				checkDownRightMove(selectedSquare.first, selectedSquare.second, onlyKills);
				checkUpLeftMove(selectedSquare.first, selectedSquare.second, onlyKills);
				checkUpRightMove(selectedSquare.first, selectedSquare.second, onlyKills);
				break;
			case square::WhiteKing:
				checkDownLeftMove(selectedSquare.first, selectedSquare.second, onlyKills);
				checkDownRightMove(selectedSquare.first, selectedSquare.second, onlyKills);
				checkUpLeftMove(selectedSquare.first, selectedSquare.second, onlyKills);
				checkUpRightMove(selectedSquare.first, selectedSquare.second, onlyKills);
				break;
			default:
				break;
			}

		}
		else
		{
			numMandatoryMoves = numPossibleMoves;
			for (int i = 0; i < numPossibleMoves; i++)
			{
				mandatoryMoves[i] = possibleMoves[i];
			}
		}
	}
	else
	{
		checkMandatoryMoves(currentSidep);
		if (numMandatoryMoves > 0)
		{
			numPossibleMoves = numMandatoryMoves;
			for (int i = 0; i < numMandatoryMoves; i++)
			{
				possibleMoves[i] = mandatoryMoves[i];
			}
		}
		else
		{
			numMandatoryMoves = 0;
			numPossibleMoves = 0;
		}
	}
}



bool GameFieldLogic::isNotOutOfBounds(int row, int colon)
{
	if (row < 0 || row > 7 || colon < 0 || colon > 3)
	{
		return false;
	}
	return true;
}

bool GameFieldLogic::areOpposite(int row, int colon)
{
	if (fieldLogic.getState(row, colon) == square::Empty)
	{
		return false;
	}
	bool result = (static_cast<int>(fieldLogic.getState(row, colon)) +
		static_cast<int>(fieldLogic.getState(selectedSquare.first, selectedSquare.second))) % 2 == 1;

	return result; // нечетной будет только сумма клеток, принадлежащих к разным сторонам

}


// т.к. у нас поле 8*4, то при ходе влево (вниз или вверх) с чётной строки, номер столбца остаётся прежним (направо - наоборот, с нечётноё), поэтому номер столбца
//мы передаем чуть более сложным выражением
void GameFieldLogic::checkUpRightMove(int row, int colon, bool killMove, bool lastLayer)
{
	int newRow = row - 1;
	int newColon = colon + ((row + 1) % 2);

	if (isNotOutOfBounds(newRow, newColon))
	{
		if (fieldLogic.getState(newRow, newColon) == square::Empty)
		{
			if (killMove == false)
			{
				possibleMoves[numPossibleMoves].first = newRow;
				possibleMoves[numPossibleMoves].second = newColon;
				numPossibleMoves++;

			}
			if (static_cast<int>(fieldLogic.getState(selectedSquare.first, selectedSquare.second)) / 3 >= 1)
			{
				checkUpRightMove(newRow, newColon, killMove, lastLayer);

			}
		}
		if (areOpposite(newRow, newColon) && lastLayer == false)
		{
			checkUpRightMove(newRow, newColon, false, true);
		}
	}
}
void GameFieldLogic::checkUpLeftMove(int row, int colon, bool killMove, bool lastLayer)
{
	int newRow = row - 1;
	int newColon = colon - (row % 2);

	if (isNotOutOfBounds(newRow, newColon))
	{
		if (fieldLogic.getState(newRow, newColon) == square::Empty)
		{
			if (killMove == false)
			{
				possibleMoves[numPossibleMoves].first = newRow;
				possibleMoves[numPossibleMoves].second = newColon;
				numPossibleMoves++;
				
			}
			if (static_cast<int>(fieldLogic.getState(selectedSquare.first, selectedSquare.second)) / 3 >= 1)
			{
				checkUpLeftMove(newRow, newColon, killMove, lastLayer);

			}
		}
		else if (areOpposite(newRow, newColon) && lastLayer == false)
		{
			checkUpLeftMove(newRow, newColon, false, true);
		}
	}
}
void GameFieldLogic::checkDownRightMove(int row, int colon, bool killMove, bool lastLayer)
{
	int newRow = row + 1;
	int newColon = colon + ((row + 1) % 2);

	if (isNotOutOfBounds(newRow, newColon))
	{
		if (fieldLogic.getState(newRow, newColon) == square::Empty)
		{
			if (killMove == false)
			{
				possibleMoves[numPossibleMoves].first = newRow;
				possibleMoves[numPossibleMoves].second = newColon;
				numPossibleMoves++;
			}
			if (static_cast<int>(fieldLogic.getState(selectedSquare.first, selectedSquare.second)) / 3 >= 1)
			{
				checkDownRightMove(newRow, newColon, killMove, lastLayer);

			}
		}
		else if (areOpposite(newRow, newColon) && lastLayer == false)
		{
			checkDownRightMove(newRow, newColon, false, true);
		}
	}
}
void GameFieldLogic::checkDownLeftMove(int row, int colon, bool killMove, bool lastLayer)
{
	int newRow = row + 1;
	int newColon = colon - (row % 2);

	if (isNotOutOfBounds(newRow, newColon))
	{
		if (fieldLogic.getState(newRow, newColon) == square::Empty)
		{
			if (killMove == false)
			{
				possibleMoves[numPossibleMoves].first = newRow;
				possibleMoves[numPossibleMoves].second = newColon;
				numPossibleMoves++;
				
			}
			if (static_cast<int>(fieldLogic.getState(selectedSquare.first, selectedSquare.second)) / 3 >= 1)
			{
				checkDownLeftMove(newRow, newColon, killMove, lastLayer);

			}
		}
		else if (areOpposite(newRow, newColon) && lastLayer == false)
		{
			checkDownLeftMove(newRow, newColon, false, true);
		}
	}
}

bool  GameFieldLogic::move(std::unique_ptr<I_Player>& currentSidep)
{

	if (std::find(possibleMoves, possibleMoves + numPossibleMoves, targetSquare) != possibleMoves + numPossibleMoves)
	{
		if (fieldLogic.move(selectedSquare.first, selectedSquare.second, targetSquare.first, targetSquare.second))
		{
			killMode = true;
			selectedSquare = targetSquare;
			targetSquare.first = -1;
			targetSquare.second = -1;
			currentSidep->setCheckersKilled()++;
			checkMoves(currentSidep, true);
			if (numPossibleMoves == 0)
			{

				killMode = false;
				return true;
			}
		}
		else
		{
			return true;
		}
	}
	return false;

}


void GameFieldLogic::makeNewGame()
{
	
	numMandatoryMoves = 0;
	numPossibleMoves = 0;
	killMode = false;
	selectedSquare.first = -1;
	selectedSquare.second = -1;
	fieldLogic.init();
}


void GameFieldLogic::checkMandatoryMoves(std::unique_ptr<I_Player>& currentSidep)
{
	numMandatoryMoves = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (currentSidep->checkSideOfSquare(j, i))
			{
				setSelectedSquare().first = j;
				setSelectedSquare().second = i;
				checkMoves(currentSidep, true);
				if (numPossibleMoves > 0)
				{
					mandatoryMoves[numMandatoryMoves++] = getSelectedSquare();
				}
			}
		}
	}
	setSelectedSquare().first = -1;
	setSelectedSquare().second = -1;
}

bool GameFieldLogic::checkAbilityToMove(std::unique_ptr<I_Player>& currentSidep)
{
	numPossibleMoves = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (currentSidep->checkSideOfSquare(j, i))
			{
				setSelectedSquare().first = j;
				setSelectedSquare().second = i;
				checkMoves(currentSidep);
				if (numPossibleMoves > 0)
				{
					return true;
				}
			}
		}
	}
	return false;
}


bool GameFieldLogic::checkMovePermition(int x, int y)
{
	if (numMandatoryMoves <= 0)
	{
		return true;
	}
	else if (std::end(mandatoryMoves) == std::find(std::begin(mandatoryMoves), std::end(mandatoryMoves), std::make_pair(x, y)))
	{
		return false;
	}
	
	return true;
}

void GameFieldLogic::highlightSpecialSquares()
{
	if (numPossibleMoves > 0)  
	{
		checkersPiecesTexture.setX(0);
		checkersPiecesTexture.setY(checkersPiecesTexture.getHeight());
		if (selectedSquare.first >= 0)
		{
			checkersPiecesTexture.render(&squareRects[selectedSquare.first][selectedSquare.second]);
		}
		for (int i = numPossibleMoves - 1; i >= 0; i--)
		{
			checkersPiecesTexture.setY(checkersPiecesTexture.getHeight() * 2);
			checkersPiecesTexture.render(&squareRects[possibleMoves[i].first][possibleMoves[i].second]);
		}
		checkersPiecesTexture.setY(0);
	}

	if (numMandatoryMoves > 0)   
	{
		checkersPiecesTexture.setX(0);
		checkersPiecesTexture.setY(checkersPiecesTexture.getHeight());
		for (int i = numMandatoryMoves - 1; i >= 0; i--)
		{
			checkersPiecesTexture.setY(checkersPiecesTexture.getHeight() * 3);
			checkersPiecesTexture.render(&squareRects[possibleMoves[i].first][possibleMoves[i].second]);
		}
		checkersPiecesTexture.setY(0);

	}
}

bool GameFieldLogic::mouseOnField(int x, int y)
{
	if (x > fieldRectT.x && x < fieldRectT.x + fieldRectT.w &&
		y > fieldRectT.y && y < fieldRectT.y + fieldRectT.h)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void GameFieldLogic::nullifySpecialSquares()
{
	selectedSquare.first = -1;
	selectedSquare.second = -1;
}