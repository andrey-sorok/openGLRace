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
			{   auto pMNGFigure = m_ProjManager->GetFMGManager();
				pMNGFigure->SetNewCoord(-10, 0);
				printf("GLUT_KEY_LEFT %d\n", key);
				break;
			}
			case 102:
			{
				auto pMNGFigure = m_ProjManager->GetFMGManager();
				pMNGFigure->SetNewCoord(10, 0);
				printf("GLUT_KEY_RIGHT %d\n", key);
				break;
			}
			case 101:
			{
				auto pMNGFigure = m_ProjManager->GetFMGManager();
				pMNGFigure->SetNewCoord(0, -10);
				printf("GLUT_KEY_UP %d\n", key);
				break;
			}
			case 103:
			{
				auto pMNGFigure = m_ProjManager->GetFMGManager();
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
			auto pMNGFigure = m_ProjManager->GetFMGManager();
			pMNGFigure->RemoveAllSelectFigures(pMNGFigure->GetObjects());
			break;
		}
		default:
			break;
	}

}

void CKeyBoard::TrackProcess(int key, int x, int y)
{
	auto pScene = m_ProjManager->GetScene();
	auto pCurModel = pScene->GetCurModel();

	auto pCenter = pCurModel->GetCenter();
	auto pMinMaxXY = pCurModel->GetMinMaxModelRect(pCurModel->GetObjects2D());
	
	int dx1 =  pMinMaxXY.second.x - pCenter.first;
	dx1 = abs(dx1);
	
	int dy1 = pCenter.second - pMinMaxXY.first.y;
	dy1 = abs(dy1);

	auto pCurPosition = pCurModel->GetCurPositionXY();
	
	double scaleX = pCurModel->GetScaleX();
	double scaleY = pCurModel->GetScaleY();

	int curX1 =  pCurPosition->x - (dx1*scaleX);
	int curX2 = pCurPosition->x + (dx1*scaleX);

	int curY1 = pCurPosition->y - (dy1*scaleY);
	int curY2 = pCurPosition->y + (dy1*scaleY);
	
	auto pConditions = m_ProjManager->GetConditions();
	std::list<double> lstLeftRightUpDoen = pConditions->GeteftRightUpBottom();
	double left = lstLeftRightUpDoen.front();
	lstLeftRightUpDoen.pop_front();
	double right = lstLeftRightUpDoen.front();
	lstLeftRightUpDoen.pop_front();
	double up = lstLeftRightUpDoen.front();
	lstLeftRightUpDoen.pop_front();
	double down = lstLeftRightUpDoen.front();
	lstLeftRightUpDoen.pop_front();

	float offse = 20.00;
	switch (key)
	{
		case 27:
		{
			break;
		}

		case 100:
		{
			if (curX1 > left)
			{
				pCurModel->SetOffset(fHorizontal, -offse);
				printf("GLUT_KEY_LEFT %d\n", key);
			}
			break;
		}

		case 102:
		{
			if (curX2 < right)
			{
				pCurModel->SetOffset(fHorizontal, +offse);
				printf("GLUT_KEY_RIGHT %d\n", key);
			}
			break;
		}

		case 101:
		{
			if ((curY1- offse) > up)
			{
				pCurModel->SetOffset(fVertical, -offse);

				printf("GLUT_KEY_UP %d\n", key);
			}
			break;
		}

		case 103:
		{
			if ((curY2+ offse) < down)
			{
				pCurModel->SetOffset(fVertical, +offse);

				printf("GLUT_KEY_DOWN %d\n", key);
			}
			break;
		}
	}
	
}
