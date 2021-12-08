#include "C2DModel.h"

#include <GL\glew.h>
#include <GL\freeglut.h>

#include "FigureBase.h"
#include "Triangle2D.h"
#include "Rect2D.h"
#include "Cycle.h"

#include "Color3D.h"
#include "Point2D.h"

C2DModel::~C2DModel()
{
}

C2DModel::C2DModel(std::vector<std::shared_ptr<CFigureBase>> InFigureModel)
{
	m_OffsetXY = new CPoint2D(0, 0);
	m_MinXY = new CPoint2D(0, 0);
	m_MaxXY = new CPoint2D(0, 0);

	m_CurPositionXY = new CPoint2D(0, 0);

	m_CenterXY = new CPoint2D(0, 0);

	m_ScaleX = 0.00;	
	m_ScaleY = 0.00;

	m_iP = 0;

	m_LenghtModel = 0;

	m_TimeSet1 = 0;

	for (auto iFigure : InFigureModel)
	{
		m_Objects2D.emplace_back(iFigure);
	}

	auto modelCenter = CalcCenterModel(m_Objects2D);

	m_CenterXY->x = modelCenter.first;
	m_CenterXY->y = modelCenter.second;
}

void C2DModel::Add2Objects2D(std::shared_ptr<CFigureBase> InObj2D)
{
	m_Objects2D.emplace_back(InObj2D);
}

std::list<float> C2DModel::GetVertex()
{
	std::list<float> lstVertex;

	if (m_Objects2D.size() == 0)
		return lstVertex;

	auto LMDSelVertexInList = [&](std::list<CPoint2D*> & lstPoints)
	{
		for (auto iPoint : lstPoints)
		{
			lstVertex.push_back(iPoint->x);
			lstVertex.push_back(iPoint->y);
		}
	};

	for (auto iFigure : m_Objects2D)
	{
		EFigure fType = iFigure->GetType();
		switch (fType)
		{	
			case fTriangle:
			{
				auto pTrian = dynamic_cast<CTriangle2D*>(iFigure.get());
				if (pTrian != nullptr)
				{
					std::list<CPoint2D*> lstPoints = pTrian->GetPoints();

					LMDSelVertexInList(lstPoints);
				}

				break;
			}

			case fRectangle:
			{
				auto pRect = dynamic_cast<CRect2D*>(iFigure.get());
				if (pRect != nullptr)
				{
					std::list<CPoint2D*> lstPoints = pRect->GetPoints();

					LMDSelVertexInList(lstPoints);
				}

				break;
			}

			case fCycle:
			{
				auto pCycle = dynamic_cast<CCycle*>(iFigure.get());
				if (pCycle != nullptr)
				{
					std::list<CPoint2D*> lstPoints = pCycle->GetPoints();

					LMDSelVertexInList(lstPoints);
				}

				break;
			}

			case fNone:
				break;

			default:
				break;
		}
		
	}
	
	return lstVertex;
}

std::pair<void*, void*> C2DModel::GetVertexArr(std::shared_ptr<CFigureBase> InObjects2D)
{
	//GLfloat vv[5][2];

	const int x = 40;
	GLfloat Vertex	[x][2];
	GLfloat Color	[x][3];

	
	auto pRect = dynamic_cast<CRect2D*>(InObjects2D.get());
	
	std::list<CPoint2D*> lstPoints =  pRect->GetPoints();
	CColor3D* color = pRect->GetColor();

	int size = lstPoints.size();
	for ( int iP = 0; iP < size; ++iP )
	{
		CPoint2D* p = lstPoints.front();
		
		Vertex[iP][0] = p->x;
		Vertex[iP][1] = p->y;

		Color[iP][0] = static_cast<float>(color->R);
		Color[iP][1] = static_cast<float>(color->G);
		Color[iP][2] = static_cast<float>(color->B);

		lstPoints.pop_front();
	}

	return std::make_pair( Vertex, Color );
}

std::pair<void*, void*> C2DModel::GetAllVrtAndColor(std::list<std::shared_ptr<CFigureBase>> InArrObjects2D, int& rtnSize)
{
	auto LMDGetColorAndCoord = [](std::shared_ptr<CFigureBase> InFigure)
	{
		std::list<CPoint2D*> rtnLst;
		CColor3D* color = new CColor3D(0,0,0);

		EFigure Type = InFigure->GetType();

		switch (Type)
		{
			case fTriangle:
			{
				auto pTrian = dynamic_cast<CTriangle2D*>(InFigure.get());
				rtnLst = pTrian->GetPoints();
				color = pTrian->GetColor();
				break;
			}
				
			case fRectangle:
			{
				auto pRect = dynamic_cast<CRect2D*>(InFigure.get());
				rtnLst = pRect->GetPoints();
				color = pRect->GetColor();
				break;
			}

			case fCycle:
			{
				auto pCycle = dynamic_cast<CCycle*>(InFigure.get());
				rtnLst = pCycle->GetPoints();
				color = pCycle->GetColor();
				break;
			}

			case fNone:
				break;
			default:
				break;
		}

		return std::make_pair(rtnLst, color);
	};


	//const int MaxSize = INT_MAX;

	GLfloat Vertex	[1024][2];
	GLfloat Color	[1024][3];

	int iP = 0;
	for (auto iFigure : InArrObjects2D)
	{

		auto Pair = LMDGetColorAndCoord(iFigure);
		CColor3D* color = new CColor3D(Pair.second->R, Pair.second->G, Pair.second->B);

		std::list<CPoint2D*> vrtList = Pair.first;
		for (auto iVrt : vrtList)
		{
			Vertex[iP][0] = iVrt->x;
			Vertex[iP][1] = iVrt->y;

			Color[iP][0] = static_cast<float>(color->R);
			Color[iP][1] = static_cast<float>(color->G);
			Color[iP][2] = static_cast<float>(color->B);

			iP++;
		}
	}

	rtnSize = iP;

	return std::make_pair(Vertex, Color);
}

std::pair<float, float> C2DModel::GetCenter()
{
	auto Pair = std::make_pair(m_CenterXY->x, m_CenterXY->y); 

	return Pair;
}

std::pair<CPoint2D, CPoint2D> C2DModel::GetMinMaxModelRect(std::list<std::shared_ptr<CFigureBase>> & InModelObjects2D)
{
	auto LMDGetMinMaxPoints = [](std::list<CPoint2D*> InPoints, std::pair<CPoint2D, CPoint2D> & MinMaxPoint)
	{
		//std::pair<CPoint2D, CPoint2D> rtnPair;

		for (auto iPoint : InPoints)
		{
			//MIN
			if (MinMaxPoint.first.x > iPoint->x)
			{
				MinMaxPoint.first.x = iPoint->x;
			}

			if (MinMaxPoint.first.y > iPoint->y)
			{
				MinMaxPoint.first.y = iPoint->y;
			}
			//MAX
			if (MinMaxPoint.second.x < iPoint->x)
			{
				MinMaxPoint.second.x = iPoint->x;
			}

			if (MinMaxPoint.second.y < iPoint->y)
			{
				MinMaxPoint.second.y = iPoint->y;
			}

		}

		return true;
	};

	std::pair<CPoint2D, CPoint2D> PairMinMax;
	CPoint2D minXY(static_cast<float>(INT_MAX), static_cast<float>(INT_MAX));
	PairMinMax.first = minXY;
	CPoint2D maxXY(0.00, 0.00);
	PairMinMax.second = maxXY;

	for (auto pFigure : InModelObjects2D)
	{
		int fType = pFigure->GetType();

		switch (fType)
		{
			case 1:
			{
				break;
			}
			case 2: //Triangle
			{
				auto pTrian = dynamic_cast<CTriangle2D*>(pFigure.get());
				std::list<CPoint2D*> lstPoints = pTrian->GetPoints();
				LMDGetMinMaxPoints(lstPoints, PairMinMax);
				break;
			}
			case 3://Rectangle
			{
				auto pRect = dynamic_cast<CRect2D*>(pFigure.get());
				std::list<CPoint2D*> lstPoints = pRect->GetPoints();
				LMDGetMinMaxPoints(lstPoints, PairMinMax);
				break;
			}
			case 4://Cycle
			{
				auto pCycle = dynamic_cast<CCycle*>(pFigure.get());
				std::list<CPoint2D*> lstPoints = pCycle->GetPoints();
				LMDGetMinMaxPoints(lstPoints, PairMinMax);
				break;
			}
			default:
			{
				break;
			}
		}

	}

	return PairMinMax;
}

std::pair<double, double> C2DModel::CalcCenterModel(std::list<std::shared_ptr<CFigureBase>>& ModelObjects2D)
{
	//std::pair<CPoint2D, CPoint2D> rtnPair;

	//auto LMDGetMinMaxPoints = [](std::list<CPoint2D*> InPoints, std::pair<CPoint2D, CPoint2D> & MinMaxPoint)
	//{
	//	//std::pair<CPoint2D, CPoint2D> rtnPair;

	//	for (auto iPoint : InPoints)
	//	{
	//		//MIN
	//		if (MinMaxPoint.first.x > iPoint->x)
	//		{
	//			MinMaxPoint.first.x = iPoint->x;
	//		}
	//		
	//		if (MinMaxPoint.first.y > iPoint->y)
	//		{
	//			MinMaxPoint.first.y = iPoint->y;
	//		}
	//		//MAX
	//		if (MinMaxPoint.second.x < iPoint->x)
	//		{
	//			MinMaxPoint.second.x = iPoint->x;
	//		}

	//		if (MinMaxPoint.second.y < iPoint->y)
	//		{
	//			MinMaxPoint.second.y = iPoint->y;
	//		}

	//	}

	//	return true;
	//};

	//std::pair<CPoint2D, CPoint2D> PairMinMax;
	//CPoint2D minXY(static_cast<float>(INT_MAX), static_cast<float>(INT_MAX));
	//PairMinMax.first = minXY;
	//CPoint2D maxXY(0.00, 0.00);
	//PairMinMax.second = maxXY;

	//for (auto pFigure : ModelObjects2D)
	//{
	//	int fType = pFigure->GetType();
	//	
	//	switch (fType)
	//	{

	//		case 1:
	//		{
	//			/*auto InLine = dynamic_cast<CLine2D*>(InCurFigure);
	//			Draw2DLine(InLine);*/
	//			break;
	//		}
	//		case 2: //Triangle
	//		{
	//			auto pTrian = dynamic_cast<CTriangle2D*>(pFigure.get());
	//			std::list<CPoint2D*> lstPoints = pTrian->GetPoints();
	//			LMDGetMinMaxPoints(lstPoints, PairMinMax);
	//			break;
	//		}
	//		case 3://Rectangle
	//		{
	//			auto pRect = dynamic_cast<CRect2D*>(pFigure.get());
	//			std::list<CPoint2D*> lstPoints = pRect->GetPoints();
	//			LMDGetMinMaxPoints(lstPoints, PairMinMax);
	//			break;
	//		}
	//		case 4://Cycle
	//		{
	//			auto pCycle = dynamic_cast<CCycle*>(pFigure.get());
	//			std::list<CPoint2D*> lstPoints = pCycle->GetPoints();
	//			LMDGetMinMaxPoints(lstPoints, PairMinMax);
	//			break;
	//		}
	//		default:
	//		{
	//			break;
	//		}
	//		}
	//	
	//}

	std::pair<CPoint2D, CPoint2D> PairMinMax = GetMinMaxModelRect(ModelObjects2D);

	auto PairCenter = std::make_pair(0.00, 0.00);

	PairCenter.first = (PairMinMax.first.x + PairMinMax.second.x) / 2;
	PairCenter.second = (PairMinMax.first.y + PairMinMax.second.y) / 2;

	SetMinMaxRectXY(PairMinMax);
	
	return PairCenter;
}

void C2DModel::SetMinMaxRectXY(std::pair<CPoint2D, CPoint2D> MinMaxPoint)
{
	m_MinXY->x = MinMaxPoint.first.x;
	m_MinXY->y = MinMaxPoint.first.y;
	
	m_MaxXY->x = MinMaxPoint.second.x;
	m_MaxXY->y = MinMaxPoint.second.y;
}

std::pair<CPoint2D, CPoint2D> C2DModel::GetMinMaxRectXY()
{
	auto minXY = CPoint2D(m_MinXY->x, m_MinXY->y);
	auto maxXY = CPoint2D(m_MaxXY->x, m_MaxXY->y);

	return std::make_pair(minXY, maxXY);
}

void C2DModel::SetOffset(EDirect InDirect, float d)
{
	switch (InDirect)
	{
		case fHorizontal:
		{
			m_OffsetXY->x += d;

			break;
		}
	
		case fVertical:
		{
			m_OffsetXY->y += d;

			break;
		}
	
		default:
			break;
	}
}

void C2DModel::SetOffset(EDirect InDirect, CPoint2D InOffset)
{
	switch (InDirect)
	{
	case fHorizontal:
	{
		m_OffsetXY->x = InOffset.x;

		break;
	}

	case fVertical:
	{
		m_OffsetXY->y = InOffset.y;

		break;
	}

	default:
		break;
	}
}

void C2DModel::SetCurPositionXY(CPoint2D InCurPositionXY)
{
	m_CurPositionXY->x = InCurPositionXY.x;
	m_CurPositionXY->y = InCurPositionXY.y;
}
