#include "C2DModel.h"

#include <GL\glew.h>
#include <GL\freeglut.h>

#include "FigureBase.h"
#include "Triangle2D.h"
#include "Rect2D.h"
#include "Cycle.h"

#include "Color3D.h"

//
//C2DModel::C2DModel()
//{
//}


C2DModel::~C2DModel()
{
}

C2DModel::C2DModel(std::vector<std::shared_ptr<CFigureBase>> InFigureModel)
{
	m_iP = 0;

	for (auto iFigure : InFigureModel)
	{
		m_Objects2D.emplace_back(iFigure);
	}
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

void C2DModel::Translate(double InX, double InY)
{
}

//
//void C2DModel::Rotate(double Angle)
//{
//}
//
//void C2DModel::Translate(double InX, double InY)
//{
//}

//std::pair<double, double> C2DModel::GetCenterModel()
//{
//	auto Pair = std::make_pair(0.00, 0.00);
//	
//	return Pair;
//}
