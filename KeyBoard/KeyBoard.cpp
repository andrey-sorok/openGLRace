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
	auto pScene = m_ProjManager->GetScene();
	auto pCurModel = pScene->GetCurModel();

	std::list<int> lstNewRectCoord = m_ProjManager->GetFMGManager()->GetChengedCarRect(pCurModel);
	int curX1 = lstNewRectCoord.front();
	lstNewRectCoord.pop_front();

	int curY1 = lstNewRectCoord.front();
	lstNewRectCoord.pop_front();

	int curX2 = lstNewRectCoord.front();
	lstNewRectCoord.pop_front();

	int curY2 = lstNewRectCoord.front();
	lstNewRectCoord.pop_front();

	auto pConditions = m_ProjManager->GetConditions();
	std::list<double> lstLeftRightUpDoen = pConditions->GetLeftRightUpBottom();
	double left = lstLeftRightUpDoen.front();
	lstLeftRightUpDoen.pop_front();
	double right = lstLeftRightUpDoen.front();
	lstLeftRightUpDoen.pop_front();
	double up = lstLeftRightUpDoen.front();
	lstLeftRightUpDoen.pop_front();
	double down = lstLeftRightUpDoen.front();
	lstLeftRightUpDoen.pop_front();

	float offset = pConditions->GetCarOffset();
	switch (key)
	{
		case 13: //Enter
		{

			m_ProjManager->GetScene()->GenerateShootTrack1(pConditions->GetWINHEIGHT());

			int i = 0;
			++i;
			break;
		}

		case 119: //w
		{
			if (curY1 > up)
			{
				if ((curY1 - offset) > up)
				{
					pCurModel->SetOffset(fVertical, -offset);
				}
				else
				{
					pCurModel->SetOffset(fVertical, -abs(curY1 - up));
				}
			}

			printf("GLUT_KEY_UP %d\n", key);

			break;
		}

		case 115: //s
		{
			if (curY2 < down)
			{
				if ((curY2 + offset) < down)
				{
					pCurModel->SetOffset(fVertical, +offset);
				}
				else
				{
					int move = up - (curY1 - offset);
					pCurModel->SetOffset(fVertical, +(down - curY2));
				}
				printf("GLUT_KEY_DOWN %d\n", key);
			}

			break;
		}

		case 100: //d
		{
			if (curX2 < right)
			{
				if ((curX2 + offset) < right)
				{
					pCurModel->SetOffset(fHorizontal, +offset);
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

		case 97: //a
		{
			if (curX1 > left)
			{
				if ((curX1 >= offset))
				{
					pCurModel->SetOffset(fHorizontal, -offset);
				}
				else
				{
					pCurModel->SetOffset(fHorizontal, -abs(curX1));
				}
				printf("GLUT_KEY_LEFT %d\n", key);
			}

			break;
		}

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
				pConditions->SetIsGenerate(false);
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
	auto pScene = m_ProjManager->GetScene();
	auto pCurModel = pScene->GetCurModel();

	std::list<int> lstNewRectCoord = m_ProjManager->GetFMGManager()->GetChengedCarRect(pCurModel);
	int curX1 = lstNewRectCoord.front();
	lstNewRectCoord.pop_front();

	int curY1 = lstNewRectCoord.front();
	lstNewRectCoord.pop_front();

	int curX2 = lstNewRectCoord.front();
	lstNewRectCoord.pop_front();

	int curY2 = lstNewRectCoord.front();
	lstNewRectCoord.pop_front();

	auto pConditions = m_ProjManager->GetConditions();
	std::list<double> lstLeftRightUpDoen = pConditions->GetLeftRightUpBottom();
	double left = lstLeftRightUpDoen.front();
	lstLeftRightUpDoen.pop_front();
	double right = lstLeftRightUpDoen.front();
	lstLeftRightUpDoen.pop_front();
	double up = lstLeftRightUpDoen.front();
	lstLeftRightUpDoen.pop_front();
	double down = lstLeftRightUpDoen.front();
	lstLeftRightUpDoen.pop_front();

	float offset = pConditions->GetCarOffset();
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
				if ((curX1 >= offset))
				{
					pCurModel->SetOffset(fHorizontal, -offset);
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
				if ((curX2 + offset) < right)
				{
					pCurModel->SetOffset(fHorizontal, +offset);
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
				if ((curY1 - offset) > up)
				{
					pCurModel->SetOffset(fVertical, -offset);
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
				if ((curY2 + offset) < down)
				{
					pCurModel->SetOffset(fVertical, +offset);
				}
				else
				{
					int move = up - (curY1 - offset);
					pCurModel->SetOffset(fVertical, +(down - curY2));
				}
				printf("GLUT_KEY_DOWN %d\n", key);
			}

			break;
		}
	}
	
}
