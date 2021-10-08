#include "Mouse.h"

#include "GL/glut.h"

#include "CoordTransform.h"
#include "ManagerFigure.h"
#include "Condition.h"

#include "Scene2D.h"

#include "Point3D.h"

#include <memory>
#include <stdio.h>


CMouse::CMouse()
{
}

CMouse::~CMouse()
{
}

void CMouse::SetFigureManager(std::shared_ptr<CManagerFigure> InMNGFigure)
{
	pMNGFigure.reset(InMNGFigure.get());
}

void CMouse::SetScene2D(std::shared_ptr<CScene2D> InScene2d)
{
	m_pScene2D.reset(InScene2d.get());
}

void CMouse::MouseClick(int button, int state, int x, int y, bool& InIsMouseMove)
{
	auto pConditions = pMNGFigure->GetConditions();

	switch (button)
	{
	case GLUT_LEFT_BUTTON:
	{
		if (state == GLUT_DOWN)
		{
			auto pConditions = pMNGFigure->GetConditions();
			pConditions->SetMouseState(state);
			pConditions->SetMouseButtonState(button);
		}
		else if (state == GLUT_UP)
		{
			auto pConditions = pMNGFigure->GetConditions();
			pConditions->SetMouseState(state);
			pConditions->SetMouseButtonState(button);

			auto pCoordTransf = std::make_unique<CCoordTransform>();
			CPoint3D p = pCoordTransf->Win2ProjCoordinate(x, y);

			GameState CurState = pConditions->GetCurGameState();
			switch (CurState)
			{
			case BeginLoading:
				break;

			case StartMenu:
			{
				GameState ChangeState = m_pScene2D->CheckStartMenuClick(p);
				pConditions->SetCurGameState(ChangeState);

				break;
			}

			case Redact:
			{
				bool IsSydebarClick = m_pScene2D->IsLeftSideBarClick(p.x, p.y);
				if (IsSydebarClick)
				{
					EFigure curFigure = m_pScene2D->GetFigureClick(p.x, p.y);
					if (curFigure != fNone)
					{
						pConditions->SetCurFigure(curFigure);
					}
					else if (m_pScene2D->ChecClickSaveAndExit(p.x, p.y))
					{
						break;
					}
					else
					{
						CColor3D CurColor = m_pScene2D->GetClickColor(x, y);
						auto pConditions = pMNGFigure->GetConditions();
						pConditions->SetCurColor(CurColor);
					}
				}
				else if (!InIsMouseMove)
				{
					auto pCoordTransf = std::make_unique<CCoordTransform>();
					CPoint3D p = pCoordTransf->Win2ProjCoordinate(x, y);
					if (!pMNGFigure->ClickedObj2D(p.x, p.y))
						pMNGFigure->CreateNewFigure(x, y, pConditions->GetCurFigure());
				}
				else
				{
					InIsMouseMove = false;
				}
				break;
			}
			case Game:
				break;

			case Choice:
				break;

			default:
				break;
			} 
		}
		break;
	}
	case GLUT_RIGHT_BUTTON:
	{
		auto pConditions = pMNGFigure->GetConditions();
		pConditions->SetMouseState(state);
		pConditions->SetMouseButtonState(button);
	}
	case 1://SCROLL_PUSH
	{
		auto pConditions = pMNGFigure->GetConditions();
		pConditions->SetMouseState(state);
		pConditions->SetMouseButtonState(button);

		break;
	}
	case 3: //SCROLL_UP
	{
		bool IsUp = false; //reverse
		pMNGFigure->SetNewScale(IsUp);
		break;
	}
	case 4: //SCROLL_DOWN
	{
		auto pConditions = pMNGFigure->GetConditions();
		pConditions->SetMouseState(state);
		pConditions->SetMouseButtonState(button);

		bool IsUp = true; //reverse
		pMNGFigure->SetNewScale(IsUp);
		break;
	}
	default:
		break;
	}
	// Force redraw
	glutPostRedisplay();
}

void CMouse::MouseMotion(int x, int y, bool& InIsMouseMove)
{
	auto pConditions = pMNGFigure->GetConditions();
	
	if (pConditions->GetMouseButtonState() == GLUT_LEFT_BUTTON)
	{
		InIsMouseMove = true;
		auto pCoordTransf = std::make_unique<CCoordTransform>();
		CPoint3D p = pCoordTransf->Win2ProjCoordinate(x, y);
		pMNGFigure->SetNewCoord(true, p.x, p.y);

		glutPostRedisplay();
	}
}

void CMouse::MousePassiveMotion(int x, int y)
{
	char buf[80];

	sprintf(buf, "Mouse coords is: x=%d; y=%d", x, y);
	glutSetWindowTitle(buf);
}
