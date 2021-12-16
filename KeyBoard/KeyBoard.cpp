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

		case 27: 
		{
			// Esc button
			auto pConditions = m_ProjManager->GetConditions();
			auto CurGAmeState = pConditions->GetCurGameState();
			if (CurGAmeState == Game)
			{
				auto pScene2D = m_ProjManager->GetScene();
				pScene2D->ClearCurModels();
				
				pConditions->SetCurGameState(StartMenu);

			}
			break;
		}
			
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
	auto pConditions = m_ProjManager->GetConditions();

	auto pScene = m_ProjManager->GetScene();
	auto pCurModel = pScene->GetCurModel();

	auto pCenter = pCurModel->GetCenter();
	auto pMinMaxXY = pCurModel->GetMinMaxModelRect(pCurModel->GetObjects2D());

	auto RectForModelInTrack = pConditions->GetRectForCarInTrack();
	double scaleX = pCurModel->GetScaleX();
	double scaleY = pCurModel->GetScaleY();

	float lengthModelY = pMinMaxXY.second.x - pMinMaxXY.first.x;
	float lengthModelX = pMinMaxXY.second.y - pMinMaxXY.first.y;

	float NewLengthX = lengthModelX * scaleX;
	float NewLengthY = lengthModelY * scaleY;

	auto pCurPosition = pCurModel->GetCurPositionXY();
	
	int curX2 = pCurPosition->x + NewLengthX / 2; 
	int curY2 = pCurPosition->y + NewLengthY / 2;
	
	int curX1 = pCurPosition->x - NewLengthX / 2;
	int curY1 = pCurPosition->y - NewLengthY / 2;

	std::list<double> lstLeftRightUpDoen = pConditions->GetLeftRightUpBottom();
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
				if ((curX1 >= offse))
				{
					pCurModel->SetOffset(fHorizontal, -offse);
				}
				else
				{
					pCurModel->SetOffset(fHorizontal, -abs(curX1));
				}
				printf("GLUT_KEY_LEFT %d\n", key);
			}

			break;
		}

		case 102:
		{
			if (curX2 < right)
			{
				if ((curX2 + offse) < right)
				{
					pCurModel->SetOffset(fHorizontal, +offse);
				}
				else
				{
					int dRX = 20;
					pCurModel->SetOffset(fHorizontal, +(right - curX2) + dRX);
				}

				printf("GLUT_KEY_RIGHT %d\n", key);
			}
			break;
		}

		case 101:
		{
			if (curY1 > up)
			{
				if ((curY1 - offse) > up)
				{
					pCurModel->SetOffset(fVertical, -offse);
				}
				else
				{
					pCurModel->SetOffset(fVertical, -abs(curY1 - up));
				}
			}
		
			printf("GLUT_KEY_UP %d\n", key);

			break;
		}

		case 103:
		{
			if (curY2 < down)
			{
				if ((curY2 + offse) < down)
				{
					pCurModel->SetOffset(fVertical, +offse);
				}
				else
				{
					int move = up - (curY1 - offse);
					pCurModel->SetOffset(fVertical, +(down - curY2));
				}
				printf("GLUT_KEY_DOWN %d\n", key);
			}

			break;
		}
	}
	
}
