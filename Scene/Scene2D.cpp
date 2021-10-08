#include "Scene2D.h"

#include "Point3D.h"

#include "FigureBase.h"
#include "Line2D.h"
#include "Rect2D.h"
#include "Triangle2D.h"
#include "Cycle.h"

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

CScene2D::CScene2D()
{
	
}


CScene2D::~CScene2D()
{
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
