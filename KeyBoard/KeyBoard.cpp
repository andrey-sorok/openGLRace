#include "KeyBoard.h"

#include <gl\freeglut.h>

#include "ManagerFigure.h"
#include "Condition.h"

#include "C2DRender.h"
#include "Scene2D.h"

#include <C2DModel.h>

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

void CKeyBoard::SetProjManager(std::shared_ptr<CProjManager> InProjManager)
{
	m_ProjManager.reset(InProjManager.get());
}

void CKeyBoard::KeyProcess(int key, int x, int y)
{
	auto pConditons = m_ProjManager->GetConditions(); //pMNGFigure->GetConditions();
	GameState curState =  pConditons->GetCurGameState();
	
	if (curState == Redact)
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
	else if (curState == Game)
	{
		TrackProcess(key, x, y);
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

void CKeyBoard::TrackProcess(int key, int x, int y)
{
	float offse = 10.00;
	switch (key)
	{
		case 27:
		{
			break;
		}

		case 100:
		{
			auto pScene = m_ProjManager->GetScene();
			auto pCurModel = pScene->GetCurModel();

			pCurModel->SetOffset(fHorizontal, -offse);

			printf("GLUT_KEY_LEFT %d\n", key);
			break;
		}

		case 102:
		{
			auto pScene = m_ProjManager->GetScene();
			auto pCurModel = pScene->GetCurModel();

			pCurModel->SetOffset(fHorizontal, +offse);

			printf("GLUT_KEY_RIGHT %d\n", key);
			break;
		}

		case 101:
		{
			auto pScene = m_ProjManager->GetScene();
			auto pCurModel = pScene->GetCurModel();

			pCurModel->SetOffset(fVertical, -offse);

			printf("GLUT_KEY_UP %d\n", key);
			break;
		}

		case 103:
		{
			auto pScene = m_ProjManager->GetScene();
			auto pCurModel = pScene->GetCurModel();

			pCurModel->SetOffset(fVertical, +offse);

			printf("GLUT_KEY_DOWN %d\n", key);
			break;
		}
	}

}
