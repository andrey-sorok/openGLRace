#include "MyMath.h"

#include "Point2D.h"

#include "FigureBase.h"

#include "Rect2D.h"
#include "Triangle2D.h"
#include "Cycle.h"

#include <stack>
#include <vector>
#include <algorithm>
#include <memory>

CMyMath::CMyMath()
{
}


CMyMath::~CMyMath()
{
}

bool CMyMath::IsPointLocation(const CPoint2D InVecBegin, const CPoint2D InVecEnd, const CPoint2D InPoint)
{
	double res = (InVecEnd.x - InVecBegin.x)*(InPoint.y - InVecBegin.y) - (InVecEnd.y - InVecBegin.y) * (InPoint.x - InVecBegin.x);
	bool IsLeft = false;
	if (res < 0.01)
	{
		IsLeft = true;
	}

	return IsLeft;
}

bool CMyMath::IsPointInTriangle(const CPoint2D InVec1Begin, const CPoint2D InVec1End, const CPoint2D InVec2Begin,
	const CPoint2D InVec2End, const CPoint2D InVec3Begin,
	const CPoint2D InVec3End, const CPoint2D InPoint)
{
	bool rtn = false;

	bool IsLeft1 = IsPointLocation(InVec1Begin, InVec1End, InPoint);
	bool IsLeft2 = IsPointLocation(InVec2Begin, InVec2End, InPoint);
	bool IsLeft3 = IsPointLocation(InVec3Begin, InVec3End, InPoint);

	if (!IsLeft1 && !IsLeft2 && !IsLeft3)
		rtn = true;

	return rtn;
}

bool CMyMath::CheckFiguresConnectivity(std::vector<CFigureBase*> InObjVector)
{
	std::stack<CFigureBase*> fStack;
	std::vector<CFigureBase*> vCrossObjects;
	
	int InObjVectorSize = InObjVector.size();
	auto pLastFigure = InObjVector[InObjVectorSize -1];
	fStack.emplace(pLastFigure);

	InObjVector.pop_back();

	while (!fStack.empty())
	{
		auto pUp = fStack.top();
		fStack.pop();

		//find connect objects
		std::vector<CFigureBase*> vConnectObjs = GetConnectObjs(InObjVector, pUp);
		
		for (auto& iObj : vConnectObjs)
		{
			fStack.push(iObj);
		}
	
		auto findeCrossObjects = std::find(vCrossObjects.begin(), vCrossObjects.end(), pUp);
		if (findeCrossObjects == vCrossObjects.end())
		{
			//add to crossObj
			vCrossObjects.emplace_back(pUp);
		}
	}

	if (vCrossObjects.size() != InObjVectorSize)
		return false;

	return true;
}

std::vector<CFigureBase*> CMyMath::GetConnectObjs(std::vector<CFigureBase*> &InObjVector, CFigureBase * InUpObj)
{
	std::vector<CFigureBase*>rtnObjs;

	std::vector<CFigureBase*>::iterator itObj = InObjVector.begin();

	while (itObj != InObjVector.end())
	{
		bool IsDescribed = ChecRectDescribed(InUpObj, *itObj);
		if (IsDescribed)
		{
			rtnObjs.emplace_back(*itObj);
			itObj = InObjVector.erase(itObj);
		}
		else
		{
			itObj++;
		}
	}

	return rtnObjs;
}

bool CMyMath::ChecRectDescribed(CFigureBase * InUpObj1, CFigureBase * InUpObj2)
{
	auto LMDGetRect = [&](CFigureBase * InUpObj)
	{
		EFigure fType = InUpObj->GetType();
		switch (fType)
		{
			case 1:
			{
				break;
			}
			case 2: //Triangle
			{
				auto pRectCoord = GetTriangleRectDescribed(InUpObj); //GetRectangleRectDescribed(InUpObj);
				return pRectCoord;
			}
			case 3://Rectangle
			{
				auto pRectCoord = GetRectangleRectDescribed(InUpObj);
				return pRectCoord;
			}
			case 4://Cycle
			{
				auto pRectCoord = GetCucleRectDescribed(InUpObj);
				return pRectCoord;
			}
			default:
			{
				break;
			}
		}
	};

	auto LMDIsRectsIntersect = [](std::pair<CPoint2D, CPoint2D> InRect1, std::pair<CPoint2D, CPoint2D> InRect2)
	{
		//P1
		if ((InRect1.first.x <= InRect2.first.x) && (InRect1.second.x >= InRect2.first.x)
			&& ((InRect1.first.y <= InRect2.first.y) && (InRect1.second.y >= InRect2.first.y)))
		{
			return true;
		}

		//P3
		if ((InRect1.first.x <= InRect2.second.x) && (InRect1.second.x >= InRect2.second.x)
			&& ((InRect1.first.y <= InRect2.second.y) && (InRect1.second.y >= InRect2.second.y)))
		{
			return true;
		}

		auto pRect = std::make_unique<CRect2D>();
		//auto P2P4Rect1 = pRect->GetP2P4(InRect1.first, InRect1.second);
		auto P2P4Rect2 = pRect->GetP2P4(InRect2.first, InRect2.second);

		//P2
		if ((InRect1.first.x <= P2P4Rect2.first.x) && (InRect1.second.x >= P2P4Rect2.first.x)
			&& ((InRect1.first.y <= P2P4Rect2.first.y) && (InRect1.second.y >= P2P4Rect2.first.y)))
		{
			return true;
		}
		
		//P4
		if ((InRect1.first.x <= P2P4Rect2.second.x) && (InRect1.second.x >= P2P4Rect2.second.x)
			&& ((InRect1.first.y <= P2P4Rect2.second.y) && (InRect1.second.y >= P2P4Rect2.second.y)))
		{
			return true;
		}

		return false;
	};

	auto Rect1 = LMDGetRect(InUpObj1);
	auto Rect2 = LMDGetRect(InUpObj2);

	if (LMDIsRectsIntersect(Rect1, Rect2))
		return true;

	if (LMDIsRectsIntersect(Rect2, Rect1))
		return true;

	return false;
}

//Figures rectangle described
std::pair<CPoint2D, CPoint2D> CMyMath::GetRectangleRectDescribed(CFigureBase * InRect)
{
	std::pair<CPoint2D, CPoint2D> rtnRect;

	auto pRect = dynamic_cast<CRect2D*>(InRect);
	if (pRect != nullptr)
	{
		std::list<CPoint2D*>lPoints = pRect->GetPoints();
		CPoint2D* P1 = lPoints.front();
		lPoints.pop_front();
		lPoints.pop_front();
		CPoint2D* P3 = lPoints.front();

		CPoint2D p1(P1->x - 3, P1->y - 3);
		CPoint2D p2(P3->x + 3, P3->y + 3);

		rtnRect = std::make_pair(p1, p2);
	}

	return rtnRect;
}

std::pair<CPoint2D, CPoint2D> CMyMath::GetTriangleRectDescribed(CFigureBase * InTrian)
{
	std::pair<CPoint2D, CPoint2D> rtnRect;

	auto pTrian = dynamic_cast<CTriangle2D*>(InTrian);
	if (pTrian != nullptr)
	{
		std::list<CPoint2D*>lPoints = pTrian->GetPoints();
		CPoint2D* P1 = lPoints.front();
		lPoints.pop_front();
		CPoint2D* P2 = lPoints.front();
		lPoints.pop_front();
		CPoint2D* P3 = lPoints.front();

		CPoint2D p1(P2->x - 3, P1->y - 3);
		CPoint2D p2(P3->x + 3, P3->y + 3);

		rtnRect = std::make_pair(p1, p2);
	}

	return rtnRect;
}

std::pair<CPoint2D, CPoint2D> CMyMath::GetCucleRectDescribed(CFigureBase * InCycle)
{
	std::pair<CPoint2D, CPoint2D> rtnRect;

	auto pCycle = dynamic_cast<CCycle*>(InCycle);
	if (pCycle != nullptr)
	{
		CPoint2D center = pCycle->GetCenter();
		double radius = pCycle->GetRadius();
		
		CPoint2D p1(center.x - radius - 3, center.y - radius - 3);
		CPoint2D p2(center.x + radius + 3, center.y + radius + 3);
		
		rtnRect = std::make_pair(p1, p2);
	}

	return rtnRect;
}
std::vector<std::vector<std::pair<CPoint2D, CPoint2D>>> CMyMath::CreateOutGreed(int InNumModels, int WinWidth, int WinHeight)
{

	int width = WinWidth;
	int height = WinHeight;

	int rows = 0;
	int cols = 0;

	int CellWidth = 0;
	int RowHeight = 0;

	if ((InNumModels > 0) && (InNumModels <= 2))
	{
		rows = 1;
		cols = 2;

		CellWidth = width / cols;
	}
	else if ((InNumModels > 2) && (InNumModels <= 4))
	{
		rows = 2;
		cols = 2;

		CellWidth = width / cols;
		RowHeight = height / rows;
	}
	else if ((InNumModels > 4) && (InNumModels <= 6))
	{
		rows = 2;
		cols = 3;

		CellWidth = width / cols;
		RowHeight = height / rows;
	}
	else if ((InNumModels > 6) && (InNumModels <= 9))
	{
		rows = 3;
		cols = 3;

		CellWidth = width / rows;
		RowHeight = height / cols;
	}
	else if ((InNumModels > 9) && (InNumModels <= 12))
	{
		rows = 3;
		cols = 4;

		CellWidth = width / cols;
		RowHeight = height / rows;
	}
	else if ((InNumModels > 12) && (InNumModels <= 16))
	{
		rows = 4;
		cols = 4;

		CellWidth = width / cols;
		RowHeight = height / rows;
	}

	std::vector<std::vector<std::pair<CPoint2D, CPoint2D>>> rtnGreed = CalcGreed(CellWidth, RowHeight, rows, cols);

	return rtnGreed;
}

std::vector<std::vector<std::pair<CPoint2D, CPoint2D>>> CMyMath::CalcGreed(int WidthCell, int HeightRow, int rows, int cols)
{
	std::vector<std::vector<std::pair<CPoint2D, CPoint2D>>> rtnGreed;

	rtnGreed.resize(rows);

	CPoint2D p1(0, 0);
	CPoint2D p3(WidthCell, HeightRow);

	for (int irow = 0; irow < rtnGreed.size(); ++irow)
	{
		rtnGreed[irow].resize(cols);

		for (int icel = 0; icel < rtnGreed[irow].size(); ++icel)
		{
			auto Pair = std::make_pair(p1, p3);
			rtnGreed[irow][icel] = Pair;

			p1.x += WidthCell;
			p3.x += WidthCell;
		}

		p1.x = 0.00;
		p3.x = WidthCell;

		p1.y += HeightRow;
		p3.y += HeightRow;
	}


	return rtnGreed;
}
//End_Figures rectangle described
