#include "HumanPlayer.h"
#include "GameFieldLogic.h"
#include <iostream>





bool HumanPlayer::selectSquare()
{
	if (fieldp->getMouseX() < 0 || fieldp->getMouseY() < 0)
	{
		return false;
	}
	int tempX = (fieldp->getMouseX() - fieldp->getFieldRectX()); // из X координты относительно экрана получаем X координату относительно начала картинки с игровым полем
	tempX -= tempX % (fieldp->getFieldRectW() / 8); // теперь tempX указывает на ближайшую левую (по отношению к X)  грань столбца поля
	tempX = tempX / (fieldp->getFieldRectW() / 8); // tempX теперь хранит номер столбца

	int tempY = (fieldp->getMouseY() - fieldp->getFieldRectY());  // тоже самое, что с tempX, только в этот раз ищем номер строки
	tempY -= tempY % (fieldp->getFieldRectH() / 8);
	tempY = tempY / (fieldp->getFieldRectH() / 8);
	fieldp->nullifyMouse();

	if ((tempX + tempY) % 2 == 1)// если сумма номеров строки и столбца делится на 2 без остатка, то клетка с этим номером  белая, неигровая
	{

		tempX = (tempX - ((tempY + 1) % 2)) / 2;// т.к. мы храним поле 8*8 в виде поля 8*4, то необходимо перевести номер столбца в подходящий для нас формат
		if (checkSideOfSquare(tempY, tempX) && fieldp->checkMovePermition(tempY, tempX))
		{
			fieldp->setSelectedSquare().first = tempY;
			fieldp->setSelectedSquare().second = tempX;
			return false;
		}
		else if (fieldp->getSquareState(tempY, tempX) == GameFieldLogic::square::Empty)
		{
			fieldp->setTargetSquare().first = tempY;
			fieldp->setTargetSquare().second = tempX;
			return true;
		}
	}
	if (fieldp->getKillMode() == false)
	{
		fieldp->setSelectedSquare().first = -1;
		fieldp->setSelectedSquare().second = -1;
	}
	return false;
}

