#include "Scene2D.h"

#include "Point3D.h"
#include "Point2D.h"

#include "FigureBase.h"
#include "Line2D.h"
#include "Rect2D.h"
#include "Triangle2D.h"
#include "Cycle.h"

#include "C2DModel.h"
#include "C2DGenModel.h"

#include "CycleProperty.h"
#include "TriangleProperty.h"

#include "MyMath.h"

#include <memory>

std::vector<std::shared_ptr<CFigureBase>> CScene2D::GetLeftSideBarObj()
{
	m_LeftSideBarObj.clear();
	m_LeftSideBarObj.shrink_to_fit();

	CColor3D color(0, 255, 0);

	auto pLine1 = std::make_shared<CLine2D>(CPoint2D(100, 0), CPoint2D(100, 1000), color);
	m_LeftSideBarObj.emplace_back(pLine1);
	//Rect
	auto pLine2 = std::make_shared<CLine2D>(CPoint2D(0, 50), CPoint2D(100, 50), color);
	m_LeftSideBarObj.emplace_back(pLine2);
	auto pRect2D = std::make_shared<CRect2D>(CPoint2D(10, 10), CPoint2D(90, 40), color);
	m_LeftSideBarObj.emplace_back(pRect2D);
	//Triangle
	auto pLine3 = std::make_shared<CLine2D>(CPoint2D(0, 100), CPoint2D(100, 100), color);
	m_LeftSideBarObj.emplace_back(pLine3);
	auto pTriangle2D = std::make_shared<CTriangle2D>(CPoint2D(50, 60), CPoint2D(10, 90), CPoint2D(90, 90), color);
	m_LeftSideBarObj.emplace_back(pTriangle2D);
	//Cycle
	auto pLine4 = std::make_shared<CLine2D>(CPoint2D(0, 150), CPoint2D(100, 150), color);
	m_LeftSideBarObj.emplace_back(pLine4);
	auto pCycle = std::make_shared<CCycle>(CPoint2D(50, 125), 20, color);
	m_LeftSideBarObj.emplace_back(pCycle);

	//CurentColor
	CColor3D baseColorBlue(0, 0, 255);
	auto pColorRect1 = std::make_shared<CRect2D>(CPoint2D(0, 150), CPoint2D(100, 200), baseColorBlue);
	m_LeftSideBarObj.emplace_back(pColorRect1);
	auto pLine5 = std::make_shared<CLine2D>(CPoint2D(0, 200), CPoint2D(100, 200), color);
	m_LeftSideBarObj.emplace_back(pLine5);

	CColor3D baseColorWhite(255, 255, 255);
	auto pColorRect2 = std::make_shared<CRect2D>(CPoint2D(0, 200), CPoint2D(100, 250), baseColorWhite);
	m_LeftSideBarObj.emplace_back(pColorRect2);
	auto pLine6 = std::make_shared<CLine2D>(CPoint2D(0, 250), CPoint2D(100, 250), color);
	m_LeftSideBarObj.emplace_back(pLine6);

	CColor3D baseColorRed(255, 0, 0);
	auto pColorRect3 = std::make_shared<CRect2D>(CPoint2D(0, 250), CPoint2D(100, 300), baseColorRed);
	m_LeftSideBarObj.emplace_back(pColorRect3);
	auto pLine7 = std::make_shared<CLine2D>(CPoint2D(0, 300), CPoint2D(100, 300), color);
	m_LeftSideBarObj.emplace_back(pLine7);

	CColor3D baseColorYellow(255, 255, 0);
	auto pColorRect4 = std::make_shared<CRect2D>(CPoint2D(0, 300), CPoint2D(100, 350), baseColorYellow);
	m_LeftSideBarObj.emplace_back(pColorRect4);
	auto pLine8 = std::make_shared<CLine2D>(CPoint2D(0, 350), CPoint2D(100, 350), color);
	m_LeftSideBarObj.emplace_back(pLine8);

	auto pLine9 = std::make_shared<CLine2D>(CPoint2D(0, 400), CPoint2D(100, 400), color);
	m_LeftSideBarObj.emplace_back(pLine9);

	//Current Figure and Color
	auto pLine10 = std::make_shared<CLine2D>(CPoint2D(0, 450), CPoint2D(100, 450), color);
	m_LeftSideBarObj.emplace_back(pLine10);
	//color
	auto pLine11 = std::make_shared<CLine2D>(CPoint2D(0, 500), CPoint2D(100, 500), color);
	m_LeftSideBarObj.emplace_back(pLine11);

	auto pLine12 = std::make_shared<CLine2D>(CPoint2D(0, 550), CPoint2D(100, 550), color);
	m_LeftSideBarObj.emplace_back(pLine12);



	return m_LeftSideBarObj;
}

std::vector<std::shared_ptr<CFigureBase>> CScene2D::GetStartMenObj()
{
	m_StartMenuObj.clear();
	m_StartMenuObj.shrink_to_fit();

	//Start
	CColor3D color(0, 255, 0);
	auto pRect2D1 = std::make_shared<CRect2D>(CPoint2D(100, 100), CPoint2D(1600, 150), color);
	m_StartMenuObj.emplace_back(pRect2D1);

	//Choice Car
	auto pRect2D2 = std::make_shared<CRect2D>(CPoint2D(100, 350), CPoint2D(1600, 400), color);
	m_StartMenuObj.emplace_back(pRect2D2);

	//Create Car
	auto pRect2D3 = std::make_shared<CRect2D>(CPoint2D(100, 650), CPoint2D(1600, 700), color);
	m_StartMenuObj.emplace_back(pRect2D3);

	return m_StartMenuObj;
}

void CScene2D::GenerateCurdModel(int WinWidth, int InCerbHeight)
{
	//Num Cerbs
	int n = 5;

	int numCurb = WinWidth / n;
	int curPosX = 0;

	CColor3D colorWhite(255, 255, 255);
	CColor3D colorBlack(0, 0, 0);
	std::vector<std::shared_ptr<CFigureBase>> Objects2D;
	//0
	/*curPosX = -numCurb;
	auto pRect0 = std::make_shared<CRect2D>(CPoint2D(static_cast<float>(-curPosX), 0), CPoint2D(static_cast<float>(curPosX + numCurb), static_cast<float>(InCerbHeight)), colorWhite);
	Objects2D.emplace_back(pRect0);*/
	//1
	auto pRect1 = std::make_shared<CRect2D>(CPoint2D(static_cast<float>(curPosX), 0), 
		CPoint2D(static_cast<float>(curPosX + numCurb), static_cast<float>(InCerbHeight)), colorWhite);
	Objects2D.emplace_back(pRect1);
	//2
	curPosX += numCurb;
	auto pRect2 = std::make_shared<CRect2D>(CPoint2D(static_cast<float>(curPosX), 0), 
		CPoint2D(static_cast<float>(curPosX + numCurb), static_cast<float>(InCerbHeight)), colorBlack);
	Objects2D.emplace_back(pRect2);
	//3
	curPosX += numCurb;
	auto pRect3 = std::make_shared<CRect2D>(CPoint2D(static_cast<float>(curPosX), 0), 
		CPoint2D(static_cast<float>(curPosX + numCurb), static_cast<float>(InCerbHeight)), colorWhite);
	Objects2D.emplace_back(pRect3);
	//4
	curPosX += numCurb;
	auto pRect4 = std::make_shared<CRect2D>(CPoint2D(static_cast<float>(curPosX), 0), 
		CPoint2D(static_cast<float>(curPosX + numCurb), static_cast<float>(InCerbHeight)), colorBlack);
	Objects2D.emplace_back(pRect4);
	//m_Сurb->Add2Objects2D(pRect4);
	//5
	curPosX += numCurb;
	auto pRect5 = std::make_shared<CRect2D>(CPoint2D(static_cast<float>(curPosX), 0), 
		CPoint2D(static_cast<float>(curPosX + numCurb), static_cast<float>(InCerbHeight)), colorWhite);
	Objects2D.emplace_back(pRect5);
	//m_Сurb->Add2Objects2D(pRect5);
	
	
	//6
	curPosX += numCurb;
	auto pRect6 = std::make_shared<CRect2D>(CPoint2D(static_cast<float>(curPosX), 0), 
		CPoint2D(static_cast<float>(curPosX + numCurb), static_cast<float>(InCerbHeight)), colorBlack);
	Objects2D.emplace_back(pRect6);
	//////7
	curPosX += numCurb;
	auto pRect7 = std::make_shared<CRect2D>(CPoint2D(static_cast<float>(curPosX), 0), 
		CPoint2D(static_cast<float>(curPosX + numCurb), static_cast<float>(InCerbHeight)), colorWhite);
	Objects2D.emplace_back(pRect7);
	
	
	//8
	curPosX += numCurb;
	auto pRect8 = std::make_shared<CRect2D>(CPoint2D(static_cast<float>(curPosX), 0),
		CPoint2D(static_cast<float>(curPosX + numCurb), static_cast<float>(InCerbHeight)), colorBlack);
	Objects2D.emplace_back(pRect8);
	//9
	curPosX += numCurb;
	auto pRect9 = std::make_shared<CRect2D>(CPoint2D(static_cast<float>(curPosX), 0),
		CPoint2D(static_cast<float>(curPosX + numCurb), static_cast<float>(InCerbHeight)), colorWhite);
	Objects2D.emplace_back(pRect9);

	//10
	curPosX += numCurb;
	auto pRect10 = std::make_shared<CRect2D>(CPoint2D(static_cast<float>(curPosX), 0),
		CPoint2D(static_cast<float>(curPosX + numCurb), static_cast<float>(InCerbHeight)), colorBlack);
	Objects2D.emplace_back(pRect10);
	//11

	//12

	m_Сurb = std::make_shared<C2DModel>(mСurb, Objects2D);
	curPosX += numCurb;
	m_Сurb->SetLenghtModel(curPosX);
}

std::vector<std::shared_ptr<C2DGenModel>> CScene2D::GenerateTrack1Models(int winWight, int winHeight,
	std::tuple<int, int, int, int> InTrackTimeNumIntervalsOneTimreIntervalMaxCurLtrackObjects)
{
	std::vector<std::shared_ptr<C2DGenModel>> vRtnTrackModels;

//	//ввести время генерации  
//	//рандомизатор типа модели
//	//рандомизатор начальной позиции
//	//рандомизатор скорости
//	//рандомизатор скорости

	int InTrackTime = 0;
	int NumInterval = 0;
	int OneTimreInterval = 0;
	int MaxTrackObj = 0;
	
	std::tie(InTrackTime, NumInterval, OneTimreInterval, MaxTrackObj) = InTrackTimeNumIntervalsOneTimreIntervalMaxCurLtrackObjects;
	
	if ((InTrackTime > 0) && (InTrackTime < OneTimreInterval))//firs Time interval
	{
		//Rects++Triangles+Cycels
		int numberObjectsGenerate = 2;
		vRtnTrackModels = Generate(winWight, winHeight, numberObjectsGenerate, MaxTrackObj);
	}
	else if ((InTrackTime > OneTimreInterval) && (InTrackTime < (OneTimreInterval * 2)))//second Time interval
	{
		//Rects++Triangles
		int numberObjectsGenerate = 1;
		vRtnTrackModels = Generate(winWight, winHeight, numberObjectsGenerate, MaxTrackObj);
	}
	else if ((InTrackTime > (OneTimreInterval * 2)) && (InTrackTime <= (OneTimreInterval * 3)))// third Time interval
	{
		//Rects
		int numberObjectsGenerate = 0;
		vRtnTrackModels = Generate(winWight, winHeight, numberObjectsGenerate, MaxTrackObj);
		
	}

	return vRtnTrackModels;
}

void CScene2D::GenerateShootTrack1(int wHeight)
{

	std::shared_ptr<C2DModel> pCurModel = GetCurModel();
	
	auto pCurPosition = pCurModel->GetCurPositionXY();
	
	auto MinMaxXYRect = pCurModel->GetMinMaxRectXY();
	
	float lengthModelX = MinMaxXYRect.second.x - MinMaxXYRect.first.x;
	float lengthModelY = MinMaxXYRect.second.y - MinMaxXYRect.first.y;
	//__

	double oldScaleX = pCurModel->GetScaleX();
	double oldScaleY = pCurModel->GetScaleY();

	float NewLengthX = static_cast<float>(lengthModelY * oldScaleX);
	float NewLengthY = static_cast<float>(lengthModelX * oldScaleY);

	int curX2 = static_cast<int>(pCurPosition->x + NewLengthX / 2);
	int curY2 = static_cast<int>(pCurPosition->y + NewLengthY / 2);

	int curX1 = static_cast<int>(pCurPosition->x - NewLengthX / 2);
	int curY1 = static_cast<int>(pCurPosition->y - NewLengthY / 2);

	auto pRect = std::make_shared<CRect2D>(CPoint2D(0, 0), CPoint2D(8, 2), CColor3D(255, 0, 255));
	std::vector<std::shared_ptr<CFigureBase>> tmpShoots;
	tmpShoots.emplace_back(pRect);

	auto pShootModel = std::make_shared<C2DModel>(mShoot, tmpShoots);

	CPoint2D* CurPosXY = pShootModel->GetCurPositionXY();

	auto offset = pCurModel->GetOffset();

	int margin = 25 + 50;
	CurPosXY->x = static_cast<float>(curX2);
	CurPosXY->y = (wHeight / 2) + offset->y;

	m_Ttrack1ShootModels.emplace_back(pShootModel);

}

void CScene2D::ClearCurModels()
{
	m_vCarsModels.clear();
	m_vCarsModels.resize(0);
	m_vCarsModels.shrink_to_fit();

	m_vModels.clear();
	m_vModels.resize(0);
	m_vModels.shrink_to_fit();

	m_Ttrack1Models.clear();
	m_Ttrack1Models.resize(0);
	m_Ttrack1Models.shrink_to_fit();
}

std::vector<std::shared_ptr<C2DGenModel>> CScene2D::Generate(int winWight, int winHeight,
	int InNumObjectsGenerate, int InMaxTrackObj)
{
	std::vector<std::shared_ptr<C2DGenModel>> rtnVecModels;

	auto mMath = std::make_unique<CMyMath>();
	int numGenObj = mMath->GenerateRandomValueInRange(1, InMaxTrackObj);

	switch (InNumObjectsGenerate)
	{
		case 0:
		{
			for (int iFigure = 0; iFigure < numGenObj; ++iFigure)
			{
				eModelType modType = mRect;

				auto pRect = std::make_shared<CRect2D>(CPoint2D(0, 0), CPoint2D(50, 50), CColor3D(255, 0, 0));

				std::vector<std::shared_ptr<CFigureBase>> InFigureModels;
				InFigureModels.emplace_back(pRect);

				auto pModel = std::make_shared<C2DGenModel>(modType, InFigureModels);
				CPoint2D* CurPosXY = pModel->GetCurPositionXY();
				
				int margin = 25 + 50;
				CurPosXY->y = static_cast<float>(mMath->GenerateRandomValueInRange(25, winHeight - margin));

				auto pRectProp = dynamic_cast<CProperty2DModel*>(pModel->GetProperty().get());
				
				int speed = mMath->GenerateRandomValueInRange(1, m_MaxTrackObjSpeed);
				int timeAfter = mMath->GenerateRandomValueInRange(0, m_TimeAfter);

				pRectProp->SetSpeed(speed);
				pRectProp->SetShowAfterTime(timeAfter);
				
				rtnVecModels.emplace_back(pModel);
			}
			break;
		}

		case 1:
		{
			for (int iFigure = 0; iFigure < numGenObj; ++iFigure) 
			{
				int intType = mMath->GenerateRandomValueInRange(6, 9);
				eModelType modType = mRect;
				
				if ((intType > 3) && (intType <= 6))
					modType = mTriangle;
				if (((intType > 6) && (intType <= 9)))
					modType = mRect;

				//eModelType modType = static_cast<eModelType>(intType);

				if (modType == mRect)
				{
					eModelType modType = mRect;

					auto pRect = std::make_shared<CRect2D>(CPoint2D(0, 0), CPoint2D(50, 50), CColor3D(255, 0, 0));

					std::vector<std::shared_ptr<CFigureBase>> InFigureModels;
					InFigureModels.emplace_back(pRect);

					auto pModel = std::make_shared<C2DGenModel>(modType, InFigureModels);
					CPoint2D* CurPosXY = pModel->GetCurPositionXY();

					int margin = 25 + 50;
					CurPosXY->y = static_cast<float>(mMath->GenerateRandomValueInRange(25, winHeight - margin));

					auto pRectProp = dynamic_cast<CProperty2DModel*>(pModel->GetProperty().get());

					int speed = mMath->GenerateRandomValueInRange(1, m_MaxTrackObjSpeed);
					int timeAfter = mMath->GenerateRandomValueInRange(0, m_TimeAfter);

					pRectProp->SetSpeed(speed);
					pRectProp->SetShowAfterTime(timeAfter);

					rtnVecModels.emplace_back(pModel);
				}
				else if (modType == mTriangle)
				{
					modType = mTriangle;

					auto pTrian = std::make_shared<CTriangle2D>(CPoint2D(0, -20), CPoint2D(0, 20), CPoint2D(-20, 0), CColor3D(255, 255, 255));
					
					std::vector<std::shared_ptr<CFigureBase>> InFigureModels;
					InFigureModels.emplace_back(pTrian);

					auto pModel = std::make_shared<C2DGenModel>(modType, InFigureModels);

					CPoint2D* CurPosXY = pModel->GetCurPositionXY();

					int margin = 25 + 50;
					CurPosXY->y = static_cast<float>(mMath->GenerateRandomValueInRange(200, winHeight - 200)); //winHeight/2;//

					auto pCTrianProp = dynamic_cast<CTriangleProperty*>(pModel->GetProperty().get());

					int speed = mMath->GenerateRandomValueInRange(1, m_MaxTrackObjSpeed);

					pCTrianProp->SetSpeed(speed);

					int IsBound = mMath->GenerateRandomValueInRange(1, 10);
					if (IsBound < 5)
					{
						pCTrianProp->SetIsUp(true);
					}
					else
					{
						pCTrianProp->SetIsUp(false);
					}

					rtnVecModels.emplace_back(pModel);
				}

			}

			break;
		}

		case 2:
		{
			//int intType = mMath->GenerateRandomValueInRange((int)mRect, (int)mTriangle);

			int intType = mMath->GenerateRandomValueInRange(0, 9);
			eModelType modType = mRect;

			if ((intType > 3) && (intType <= 6))
				modType = mTriangle;
			if (((intType > 6) && (intType <= 9)))
				modType = mCycle;
			//eModelType modType = static_cast<eModelType>(intType);

			if (modType == mRect)
			{
				eModelType modType = mRect;

				auto pRect = std::make_shared<CRect2D>(CPoint2D(0, 0), CPoint2D(50, 50), CColor3D(255, 0, 0));

				std::vector<std::shared_ptr<CFigureBase>> InFigureModels;
				InFigureModels.emplace_back(pRect);

				auto pModel = std::make_shared<C2DGenModel>(modType, InFigureModels);
				CPoint2D* CurPosXY = pModel->GetCurPositionXY();

				int margin = 25 + 50;
				CurPosXY->y = static_cast<float>(mMath->GenerateRandomValueInRange(25, winHeight - margin));

				auto pRectProp = dynamic_cast<CProperty2DModel*>(pModel->GetProperty().get());

				int speed = mMath->GenerateRandomValueInRange(1, m_MaxTrackObjSpeed);
				int timeAfter = mMath->GenerateRandomValueInRange(0, m_TimeAfter);

				pRectProp->SetSpeed(speed);
				pRectProp->SetShowAfterTime(timeAfter);

				rtnVecModels.emplace_back(pModel);
			}
			else if (modType == mTriangle)
			{
				modType = mTriangle;

				auto pTrian = std::make_shared<CTriangle2D>(CPoint2D(0, -20), CPoint2D(0, 20), CPoint2D(-20, 0), CColor3D(255, 255, 255));

				std::vector<std::shared_ptr<CFigureBase>> InFigureModels;
				InFigureModels.emplace_back(pTrian);

				auto pModel = std::make_shared<C2DGenModel>(modType, InFigureModels);

				CPoint2D* CurPosXY = pModel->GetCurPositionXY();

				int margin = 25 + 50;
				CurPosXY->y = static_cast<float>(mMath->GenerateRandomValueInRange(200, winHeight-200));//winHeight / 2;//

				auto pCTrianProp = dynamic_cast<CTriangleProperty*>(pModel->GetProperty().get());

				int speed = mMath->GenerateRandomValueInRange(1, m_MaxTrackObjSpeed);

				pCTrianProp->SetSpeed(speed);

				int IsBound = mMath->GenerateRandomValueInRange(1, 10);
				if (IsBound < 5)
				{
					pCTrianProp->SetIsUp(true);
				}
				else
				{
					pCTrianProp->SetIsUp(false);
				}

				rtnVecModels.emplace_back(pModel);
			}
			else if (modType == mCycle)
			{
				modType = mCycle;

				auto pCycle = std::make_shared<CCycle>(CPoint2D(0, 0), 20.00, CColor3D(255, 255, 0));
				
				std::vector<std::shared_ptr<CFigureBase>> InFigureModels;
				InFigureModels.emplace_back(pCycle);

				auto pModel = std::make_shared<C2DGenModel>(modType, InFigureModels);

				CPoint2D* CurPosXY = pModel->GetCurPositionXY();

				int margin = 25 + 50;
				CurPosXY->y = static_cast<float>(mMath->GenerateRandomValueInRange(200, winHeight - 200));// winHeight / 2;//mMath->GenerateRandomValueInRange(25, winHeight - margin);
				
				auto pCycleProp = dynamic_cast<CCycleProperty*>(pModel->GetProperty().get());

				int speed = mMath->GenerateRandomValueInRange(2, m_MaxTrackObjSpeed);
				pCycleProp->SetSpeed(speed);
				
				int angel = mMath->GenerateRandomValueInRange(30, 80);
				pCycleProp->SetMoveAngel(angel);

				int IsBound = mMath->GenerateRandomValueInRange(1, 10);
				if (IsBound < 5)
				{
					pCycleProp->SetIsRebound(false);
				}
				else
				{
					pCycleProp->SetIsRebound(true);
				}
				rtnVecModels.emplace_back(pModel);
			}

			break;
		}
		
		default:
			break;
	}

	return rtnVecModels;
}

CScene2D::CScene2D()
{	
	m_MaxTrackObjSpeed = 8;
	m_TimeAfter = 5000;
}

CScene2D::~CScene2D()
{
}

void CScene2D::AddModel(std::shared_ptr<C2DModel> InModel)
{
	//eModelType iP = InModel->GetiP();
	//InModel->SetiP(iP);
	m_vModels.emplace_back(InModel);
}

std::shared_ptr<C2DModel> CScene2D::GetModel(int InNumModel)
{
	return m_vModels[InNumModel];
}

void CScene2D::AddCarModels(std::vector<std::shared_ptr<CFigureBase>> InCarModels)
{
	m_vCarsModels.emplace_back(InCarModels);
}

std::vector<std::shared_ptr<CFigureBase>> CScene2D::GetDrawRedactObjCondition()
{
	std::vector<std::shared_ptr<CFigureBase>> LeftSideBarObj = GetLeftSideBarObj();
	std::vector<std::shared_ptr<CFigureBase>> rtnObjects;

	rtnObjects.insert(rtnObjects.end(), LeftSideBarObj.begin(), LeftSideBarObj.end());
	return rtnObjects;
}

std::vector<std::shared_ptr<CFigureBase>> CScene2D::GetDrawStartMenuObjCondition()
{
	std::vector<std::shared_ptr<CFigureBase>> rtnObjects = GetStartMenObj();
	return rtnObjects;
}

bool CScene2D::IsLeftSideBarClick(int InX, int InY)
{

	if (((InX > 0) && (InX < 100)
		&& (InY > 0) && (InY < 1000)))
	{
		return true;
	}

	return false;
}

EFigure CScene2D::GetFigureClick(int InX, int InY)
{
	if ((InX > 0) && (InX < 100)
		&& (InY > 0) && (InY < 50))
	{
		return fRectangle;
	}

	if ((InX > 0) && (InX < 100)
		&& (InY > 50) && (InY < 100))
	{
		return fTriangle;
	}

	if ((InX > 0) && (InX < 100)
		&& (InY > 100) && (InY < 140))
	{
		return fCycle;
	}

	return fNone;
}

bool CScene2D::ChecClickSaveAndExit(int InX, int InY)
{
	if ((InX > 0) && (InX < 100)
		&& (InY > 450) && (InY < 500))
	{
		return true;
	}

	return false;
}

bool CScene2D::ChecClickSave(int InX, int InY)
{
	if ((InX > 0) && (InX < 100)
		&& (InY > 500) && (InY < 550))
	{
		return true;
	}

	return false;
}

CColor3D CScene2D::GetClickColor(int InX, int InY)
{
	CColor3D color(0, 0, 0);
	
	if((InX > 0) && (InX < 100)
		&& (InY > 150) && (InY < 200))
	{
		color = CColor3D(0, 0, 255);
	}
	
	if ((InX > 0) && (InX < 100)
		&& (InY > 200) && (InY < 250))
	{
		color = CColor3D(255, 255, 255);
	}
	
	if ((InX > 0) && (InX < 100)
		&& (InY > 250) && (InY < 300))
	{
		color = CColor3D(255, 0, 0);
	}
	
	if ((InX > 0) && (InX < 100)
		&& (InY > 300) && (InY < 350))
	{
		color = CColor3D(255, 255, 0);
	}
	
	return color;
}

GameState CScene2D::CheckStartMenuClick(CPoint3D InPointClick)
{

	if ((InPointClick.x > 100) && (InPointClick.x < 1600) && (InPointClick.y > 100) && (InPointClick.y < 150))
	{
		return Game;
	}
	
	if ((InPointClick.x > 100) && (InPointClick.x < 1600) && (InPointClick.y > 350) && (InPointClick.y < 400))
	{
		return Choice;
	}
	
	if ((InPointClick.x > 100) && (InPointClick.x < 1600) && (InPointClick.y > 650) && (InPointClick.y < 700))
	{
		return Redact;
	}

	return StartMenu;
}

std::shared_ptr<C2DModel> CScene2D::GetChoceModel(std::vector<std::vector<std::pair<CPoint2D, CPoint2D>>> vPointGrid, CPoint3D p)
{
	int modelNum = -1;

	for (int i = 0; i < vPointGrid.size(); ++i)
	{
		for (int j = 0; j < vPointGrid[i].size(); ++j)
		{
			auto BegEndpoints = vPointGrid[i][j];
			if (((p.x > BegEndpoints.first.x) && (p.x < BegEndpoints.second.x))
				&& (p.y > BegEndpoints.first.y) && (p.y < BegEndpoints.second.y))
			{
				modelNum = ((1 * i) + i) + (i + j); //индексы матрицы 3x3
			}
		}
	}
	
	std::shared_ptr<C2DModel> pModel = nullptr;
	if (modelNum < m_vModels.size())
	{
		pModel = m_vModels[modelNum];
	}

	
	return pModel;
}
