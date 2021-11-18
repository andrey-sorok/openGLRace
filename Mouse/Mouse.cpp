#include "Mouse.h"

#include "GL/glut.h"

#include "CoordTransform.h"
#include "ManagerFigure.h"
#include "Condition.h"

#include "Scene2D.h"

#include "Point3D.h"

#include "ClassBinaryFile.h"

#include "BinFile.h"

#include <memory>
#include <stdio.h>

#include "MyMath.h"

#include "C2DModel.h"


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

					if (ChangeState == Choice)
					{
						auto pBinFile = std::make_unique<CBinFile>();
						std::vector<std::string> vPathToModelsFiles = pBinFile->ReadNamesFiles("Cars");
						
						pConditions->SetPaths2Models(vPathToModelsFiles);
						int NumModels = vPathToModelsFiles.size();

						//__
						//NumModels = 1;
						//__

						for (int iModel = 0; iModel < NumModels; ++iModel)
						{
							auto CarsModels = pBinFile->ReadFile(vPathToModelsFiles[iModel]);	
							m_pScene2D->AddCarModels(CarsModels);

							pBinFile->CloseFile();
						}	
						auto pMMath = std::make_unique<CMyMath>();
						//pConditions->SetCurGameState(StartMenu);
						std::vector<std::vector<std::pair<CPoint2D, CPoint2D>>> vGred = pMMath->CreateOutGreed(NumModels, pConditions->GetWINWIDTH(), pConditions->GetWINHEIGHT());
						pConditions->SetOutModelsGreed(vGred);
					//__
						//std::vector<std::shared_ptr<CFigureBase>> vFirstModel = m_pScene2D->GetCarModels()[0];
						//	//vCarsModels[0];
						//std::vector<std::shared_ptr<CFigureBase>> tmpVec;
						//tmpVec.push_back(vFirstModel[1]);
						//tmpVec.push_back(vFirstModel[2]);
						//tmpVec.push_back(vFirstModel[3]);
						//tmpVec.push_back(vFirstModel[4]);

						//auto pC2DModel1 = std::make_shared<C2DModel>(tmpVec);
						//m_pScene2D->AddModel(pC2DModel1);
					//__
					}

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
							//check connectivity
							auto pMMath = std::make_unique<CMyMath>();
							std::vector<CFigureBase*> pObjects = pMNGFigure->GetAll2DObjects();
							bool IsConnect = pMMath->CheckFiguresConnectivity(pObjects);
							if (IsConnect == false)
								return;

							//save to binary file
							auto pBinFile = std::make_unique<CBinFile>();
							std::string Ext = "race";
							int NumCars = pBinFile->GetNumFiles(pConditions->GetCarsFolder(), Ext);
							pConditions->SetNumCars(NumCars);

							pBinFile->CreateOutFile(pConditions->GetCarsFolder(), out, pConditions->GetNumCars());

							int maxSize = pMNGFigure->GetObjecs2DSize();
							
							for (int iFigure = 0; iFigure < maxSize; ++iFigure)
							{
								auto pFigure = pMNGFigure->GetObject2D(iFigure);
								pBinFile->WriteFile(pFigure);
							}
							
							pBinFile->CloseFile();

							pConditions->SetCurGameState(StartMenu);

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
				{
					int i = 0;
					++i;
					break;
				}
					
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
