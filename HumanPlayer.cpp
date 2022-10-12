#include "HumanPlayer.h"
#include "GameFieldLogic.h"
#include <iostream>





bool HumanPlayer::selectSquare()
{
	if (fieldp->getMouseX() < 0 || fieldp->getMouseY() < 0)
	{
		return false;
	}
	int tempX = (fieldp->getMouseX() - fieldp->getFieldRectX()); // �� X ��������� ������������ ������ �������� X ���������� ������������ ������ �������� � ������� �����
	tempX -= tempX % (fieldp->getFieldRectW() / 8); // ������ tempX ��������� �� ��������� ����� (�� ��������� � X)  ����� ������� ����
	tempX = tempX / (fieldp->getFieldRectW() / 8); // tempX ������ ������ ����� �������

	int tempY = (fieldp->getMouseY() - fieldp->getFieldRectY());  // ���� �����, ��� � tempX, ������ � ���� ��� ���� ����� ������
	tempY -= tempY % (fieldp->getFieldRectH() / 8);
	tempY = tempY / (fieldp->getFieldRectH() / 8);
	fieldp->nullifyMouse();

	if ((tempX + tempY) % 2 == 1)// ���� ����� ������� ������ � ������� ������� �� 2 ��� �������, �� ������ � ���� �������  �����, ���������
	{

		tempX = (tempX - ((tempY + 1) % 2)) / 2;// �.�. �� ������ ���� 8*8 � ���� ���� 8*4, �� ���������� ��������� ����� ������� � ���������� ��� ��� ������
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

