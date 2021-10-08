#include "ManagerFigure.h"

#include "CoordTransform.h"
#include "Selector.h"

#include "Condition.h"

#include "Point3D.h"
#include "Rect2D.h"
#include "Triangle2D.h"
#include "Cycle.h"
#include "CoordTransform.h"
#include "MyMath.h"

#include <algorithm>
#include <memory>

CManagerFigure::CManagerFigure()
{
	m_Selector = std::make_unique<CSelector>();
	m_NumObjects = 0;
}


CManagerFigure::~CManagerFigure()
{
}

std::unique_ptr<CSelector> CManagerFigure::GetSelector()
{
	auto rtnSelector = std::unique_ptr<CSelector>(m_Selector.get());
	
	return rtnSelector;
}

void CManagerFigure::CreateNewFigure(int x, int y)
{
	auto pCoordTransf = std::make_unique<CCoordTransform>();
	CPoint3D pCenterRect = pCoordTransf->Win2ProjCoordinate(x, y);
	
	double deltaRect = 6.00;
	auto pNewRect = new CRect2D(pCenterRect.x, pCenterRect.y, deltaRect);
	AddObject2D(pNewRect);
}

void CManagerFigure::CreateNewFigure(int InX, int InY, EFigure InCurFigure)
{
	switch (InCurFigure)
	{

		case fPoint:
			break;
		case fLine:
			break;
		case fTriangle:
		{
			auto pCoordTransf = std::make_unique<CCoordTransform>();
			CPoint3D pCenterRect = pCoordTransf->Win2ProjCoordinate(InX, InY);

			auto pConditions = GetConditions();
			auto CurColor = pConditions->GetCurColor();

			auto pNewTriangle = new CTriangle2D(pCenterRect.x, pCenterRect.y, CurColor);
			AddObject2D(pNewTriangle);
		}
			break;
		case fRectangle:
		{
			auto pCoordTransf = std::make_unique<CCoordTransform>();
			CPoint3D pCenterRect = pCoordTransf->Win2ProjCoordinate(InX, InY);

			double deltaRect = 6.00;
			auto pConditions = GetConditions();
			auto CurColor = pConditions->GetCurColor();			
			auto pNewRect = new CRect2D(pCenterRect.x, pCenterRect.y, CurColor);

			AddObject2D(dynamic_cast<CFigureBase*>(pNewRect));

			break;
		}
			
		case fCycle:
		{
			auto pCoordTransf = std::make_unique<CCoordTransform>();
			CPoint3D pCenterRCycle = pCoordTransf->Win2ProjCoordinate(InX, InY);
			
			auto pConditions = GetConditions();
			auto CurColor = pConditions->GetCurColor();
			
			auto pNewCycle = new CCycle(CPoint2D(pCenterRCycle.x, pCenterRCycle.y), CurColor);
			AddObject2D(pNewCycle);

			break;
		}


		case fCube:
			break;
		default:
			break;
	}
}

bool CManagerFigure::AddObject2D( CFigureBase * inFigure )
{
	//for (int iFig = 0; iFig < m_Ojects2D.size(); iFig++)
	//{
	inFigure->SetIndObject2D(m_NumObjects);
	m_NumObjects++;
	m_Ojects2D.emplace_back(inFigure);
	//}

	return true;
}

CFigureBase * CManagerFigure::GetObject2D(int Ind)
{
	for (auto it : m_Ojects2D)
	{
		int Index = it->GetIndObject2D();
		if (Index == Ind)
			return it;
	}

	return nullptr;
}

void CManagerFigure::SetIndObjecyt2D(CFigureBase * inFigure)
{
	int size = m_Ojects2D.size();
	inFigure->SetIndObject2D(size);
}

bool CManagerFigure::ClickedObj2D(int x, int y)
{
	for (auto& pFigure : m_Ojects2D)
	{
		EFigure nFigure = pFigure->GetType();	
		switch (nFigure)
		{
			case fPoint:
				break;
	
			case fLine:
				break;
	
			case fTriangle:
			{
				CTriangle2D* pTrian = dynamic_cast<CTriangle2D*>(pFigure);
				std::list<CPoint2D*> lstTrianPoints = pTrian->GetPoints();
	
				CPoint2D* p1 = lstTrianPoints.front();
				lstTrianPoints.pop_front();
				CPoint2D* p2 = lstTrianPoints.front();
				lstTrianPoints.pop_front();
				CPoint2D* p3 = lstTrianPoints.front();
	
				auto pMath = std::make_unique<CMyMath>();
				bool IsPointInTrian = pMath->IsPointInTriangle(*p1, *p3, *p3, *p2, *p2, *p1, CPoint2D(x, y));

				if (IsPointInTrian)
				{
					auto pConditions = GetConditions();
					m_Selector.get()->SetSelection(pTrian, pConditions->GetCurColor());
					return true;
				}
	
				break;
			}

			case fRectangle:
			{
				CRect2D* pRect = dynamic_cast<CRect2D*>(pFigure);
				std::list<CPoint2D*> lstRectPoints = pRect->GetPoints();
	
				CPoint2D* p1 = lstRectPoints.front();
				lstRectPoints.pop_front();
				lstRectPoints.pop_front();
				CPoint2D* p3 = lstRectPoints.front();
	
				if ( (x > p1->x) && (x < p3->x)
					&& (y > p1->y) && (y < p3->y) )
				{
					auto pConditions = GetConditions();
					m_Selector.get()->SetSelection(pRect, pConditions->GetCurColor());
					return true;
				}
	
				break;
			}

			case fCycle:
			{
				CCycle* pCycle = dynamic_cast<CCycle*>(pFigure);

				int NumSeg = pCycle->GetNumSegments();
				CPoint2D Center = pCycle->GetCenter();
				double Radius = pCycle->GetRadius();

				double R2 = Radius* Radius;
				double XYPlace = (x - Center.x) * (x - Center.x) + (y - Center.y) * (y - Center.y);

				if (XYPlace <= R2)
				{
					auto pConditions = GetConditions();
					m_Selector.get()->SetSelection(pCycle, pConditions->GetCurColor());
					return true;
				}
					
				break;
			}
				
			case fCube:
				break;
	
			default:
				break;
			}
	}

	return false;
}

bool CManagerFigure::SetNewCoord(int x, int y)
{
	std::vector<CFigureBase*>& vSelectObjects = m_Selector->GetSelectObjects();
	for (auto& pFigure : vSelectObjects)
	{
		EFigure f = pFigure->GetType();
		switch (f)
		{
			case fPoint:
				break;
	
			case fLine:
				break;
	
			case fTriangle:
			{
				auto pTriang = dynamic_cast<CTriangle2D*>(pFigure);
				bool IsInWindow = pTriang->CheckInWindow(1, false, CPoint2D(x, y), m_pConditions->GetWINWIDTH(), m_pConditions->GetWINHEIGHT());
				break;
			}
			
			case fRectangle:
			{
				auto pRect = dynamic_cast<CRect2D*>(pFigure);
				bool IsInWindow = pRect->CheckInWindow(1, false, CPoint2D(x, y), m_pConditions->GetWINWIDTH(), m_pConditions->GetWINHEIGHT());
				break;
			}

			case fCycle:
			{
				auto pCycle = dynamic_cast<CCycle*>(pFigure);
				bool IsInWindow = pCycle->CheckInWindow(1, false, CPoint2D(x, y), m_pConditions->GetWINWIDTH(), m_pConditions->GetWINHEIGHT());
				//pCycle->SetDelta(x, y);
				break;
			}

			default:
				break;
		}
	}
	return true;
}

bool CManagerFigure::SetNewCoord(bool IsMouse, const int x, const int y)
{
	if (IsMouse)
	{
		std::vector<CFigureBase*>& vSelectObjects = m_Selector->GetSelectObjects();
		for (auto& pFigure : vSelectObjects)
		{
			EFigure nFigure = pFigure->GetType();
			switch (nFigure)
			{
				case fPoint:
					break;

				case fLine:
					break;

				case fTriangle:
				{
					auto pTrian = dynamic_cast<CTriangle2D*>(pFigure);
					auto pMath = std::make_unique<CMyMath>();

					std::list<CPoint2D*> lstTrianPoints = pTrian->GetPoints();
					CPoint2D* p1 = lstTrianPoints.front();
					lstTrianPoints.pop_front();
					CPoint2D* p2 = lstTrianPoints.front();
					lstTrianPoints.pop_front();
					CPoint2D* p3 = lstTrianPoints.front();

					bool IsPointInTrian = pMath->IsPointInTriangle(*p1, *p3, *p3, *p2, *p2, *p1, CPoint2D(x, y));

					if (IsPointInTrian)
					{
						bool IsInWindow = pTrian->CheckInWindow(2, false, CPoint2D(x, y), m_pConditions->GetWINWIDTH(), m_pConditions->GetWINHEIGHT());
						//pTrian->SetNewCoord(x, y);
						break;
					}
					break;
				}

				case fRectangle:
				{
					auto pRect = dynamic_cast<CRect2D*>(pFigure);
					std::list<CPoint2D*> lstRectPoints = pRect->GetPoints();
					CPoint2D* p1 = lstRectPoints.front();
					lstRectPoints.pop_front();
					lstRectPoints.pop_front();
					CPoint2D* p3 = lstRectPoints.front();

					if ((x > p1->x) && (x < p3->x)
						&& (y > p1->y) && (y < p3->y))
					{
						bool IsInWindow = pRect->CheckInWindow(2, false, CPoint2D(x, y), m_pConditions->GetWINWIDTH(), m_pConditions->GetWINHEIGHT());
						
						break;
					}
					break;
				}
				case fCycle:
				{
					auto pCycle = dynamic_cast<CCycle*>(pFigure);
					
					int NumSeg = pCycle->GetNumSegments();
					CPoint2D Center = pCycle->GetCenter();
					double Radius = pCycle->GetRadius();

					double R2 = Radius* Radius;
					double XYPlace = (x - Center.x) * (x - Center.x) + (y - Center.y) * (y - Center.y);

					if (XYPlace <= R2)
					{
						bool IsInWindow = pCycle->CheckInWindow(2, false, CPoint2D(x, y), m_pConditions->GetWINWIDTH(), m_pConditions->GetWINHEIGHT());
						return true;
					}

					break;
				}

			}
		}
		return true;
	}
	return false;
}

bool CManagerFigure::SetNewScale(bool IsUp)
{
	std::vector<CFigureBase*>& vSelectObjects = m_Selector->GetSelectObjects();
	for (auto& pFigure : vSelectObjects)
	{
		EFigure nFigure = pFigure->GetType();
		switch (nFigure)
		{
			case fPoint:
				break;
	
			case fLine:
				break;
	
			case fTriangle:
			{
				auto pTriang = dynamic_cast<CTriangle2D*>(pFigure);
				bool IsInWindow = pTriang->CheckInWindow(0, IsUp, CPoint2D(0, 0), m_pConditions->GetWINWIDTH(), m_pConditions->GetWINHEIGHT());
				break;
			}
			
			case fRectangle:
			{		
				auto pRect = dynamic_cast<CRect2D*>(pFigure);
				bool IsInWindow = pRect->CheckInWindow(0, IsUp, CPoint2D(0, 0), m_pConditions->GetWINWIDTH(), m_pConditions->GetWINHEIGHT());
				break;
			}

			case fCycle:
			{
				auto pCycle= dynamic_cast<CCycle*>(pFigure);
				bool IsInWindow = pCycle->CheckInWindow(0, IsUp, CPoint2D(0, 0), m_pConditions->GetWINWIDTH(), m_pConditions->GetWINHEIGHT());
				//pCycle->SetNewScale(IsUp);
				break;
			}
		}
	}
	return true;
}

bool CManagerFigure::RemoveAllSelectFigures(std::vector<CFigureBase*>& Objects2D)
{
	std::vector<CFigureBase*>& vSelectObjects = m_Selector.get()->GetSelectObjects();

	
	for (auto& pFigure : vSelectObjects)
	{
		auto fnd = std::find(Objects2D.begin(), Objects2D.end(), pFigure);
		if (fnd != Objects2D.end())
		{
			auto new_end(std::remove(Objects2D.begin(), Objects2D.end(), *fnd));
			Objects2D.erase(new_end, Objects2D.end());
			
			auto pRect = dynamic_cast<CRect2D*>(pFigure);
			delete pRect;
			pRect = nullptr;
		}
	}
	
	vSelectObjects.erase(vSelectObjects.begin(), vSelectObjects.end());

	vSelectObjects.resize(0);
	vSelectObjects.shrink_to_fit();
	return true;
}