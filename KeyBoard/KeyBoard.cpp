#include "KeyBoard.h"

#include "ManagerFigure.h"

#include <stdio.h>

CKeyBoard::CKeyBoard()
{
}


CKeyBoard::~CKeyBoard()
{
}

void CKeyBoard::SetFigureManager(std::shared_ptr<CManagerFigure> InMNGFigure)
{
	pMNGFigure.reset(InMNGFigure.get());
}

void CKeyBoard::KeyProcess(int key, int x, int y)
{
	switch (key)
	{
		case 27:
		{
			break;
		}
		case 100:
		{
			pMNGFigure->SetNewCoord(-10, 0);
			printf("GLUT_KEY_LEFT %d\n", key);
			break;
		}
		case 102:
		{
			pMNGFigure->SetNewCoord(10, 0);
			printf("GLUT_KEY_RIGHT %d\n", key);
			break;
		}
		case 101:
		{
			pMNGFigure->SetNewCoord(0, -10);
			printf("GLUT_KEY_UP %d\n", key);
			break;
		}
		case 103:
		{
			pMNGFigure->SetNewCoord(0, 10);
			printf("GLUT_KEY_DOWN %d\n", key);
			break;
		}
	}
}

void CKeyBoard::KeyStroke(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'q': // Exit
				  //exit(0);
			break;
		case 'n': // New game
				  //init();
			break;
		case 'h':
			break;
		case 27: // Esc button
				 //exit(0);
			break;
		case 127: // Delete button
		{
			pMNGFigure->RemoveAllSelectFigures(pMNGFigure->GetObjects());
			break;
		}
		default:
			break;
	}

}
