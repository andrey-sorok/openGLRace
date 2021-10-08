#include "Selector.h"

#include "FigureBase.h"
#include "ManagerFigure.h"

#include "Rect2D.h"
#include "Triangle2D.h"
#include "Cycle.h"

#include <algorithm>

CSelector::CSelector()
{
	m_SelectColor(0, 255, 0);
}


CSelector::~CSelector()
{
}

void CSelector::SetSelection(CFigureBase* pInFigure, CColor3D InCurColor)
{
	int i = 0;
	for (auto& pSelectFigure : m_SelectOjects2D)
	{
		if (pSelectFigure == pInFigure)
		{
			EFigure nFigure = pInFigure->GetType();
			switch (nFigure)
			{
				case fPoint:
					break;
	
				case fLine:
					break;
	
				case fTriangle:
				{
					auto pFig = dynamic_cast<CTriangle2D*>(pInFigure);
					if (pFig != nullptr)
					{
						pFig->SetColor(InCurColor);
					}
	
					m_SelectOjects2D.erase(m_SelectOjects2D.begin() + i);
	
					return;
				}
				
				case fRectangle:
				{
					auto pFig = dynamic_cast<CRect2D*>(pInFigure);
					if (pFig != nullptr)
					{
						pFig->SetColor(InCurColor);
					}
	
					m_SelectOjects2D.erase(m_SelectOjects2D.begin() + i);
	
					return;
				}

				case fCycle:
				{
					auto pFig = dynamic_cast<CCycle*>(pInFigure);
					if (pFig != nullptr)
					{
						pFig->SetColor(InCurColor);
					}

					m_SelectOjects2D.erase(m_SelectOjects2D.begin() + i);

					return;
				}
			}
		}

		++i;
	}
	
	pInFigure->SetColor(m_SelectColor);
	m_SelectOjects2D.emplace_back(pInFigure);
}