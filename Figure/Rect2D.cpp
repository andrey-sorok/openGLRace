#include "Rect2D.h"
#include "Color3D.h"

#include <Windows.h>

CRect2D::CRect2D()
{
	m_IndOjects2D = -1;

	m_Scale = 2.00;

	m_deltaRect = 6.00;

	m_P1 (0.00, 0.00);
	m_P3 (0.00, 0.00);

	m_P2(0.00, 0.00);
	m_P4(0.00, 0.00);

	m_Color (0, 0, 0);
}

CRect2D::CRect2D(CPoint2D inP1, CPoint2D inP3, CColor3D inColor)
{
	m_fType = fRectangle;

	m_deltaRect = 6.00;
	m_Scale = 2.00;

	m_P1 = inP1;
	m_P3 = inP3;

	auto pairP2P4 = GetP2P4(m_P1, m_P3);

	m_P2 = pairP2P4.first;
	m_P4 = pairP2P4.second;

	m_Color = inColor;
}

/*CRect2D::CRect2D(float x, float y, CColor3D inColor)
{
	m_fType = fRectangle;

	m_deltaRect = 6.00;
	m_Scale = 2.00;

	m_P1.x = x - m_deltaRect;
	m_P1.y = y - m_deltaRect;

	m_P3.x = x + m_deltaRect;
	m_P3.y = y + m_deltaRect;

	auto pairP2P4 = GetP2P4(m_P1, m_P3);

	m_P2 = pairP2P4.first;
	m_P4 = pairP2P4.second;

	m_Color = inColor;
}*/

CRect2D::CRect2D(int x, int y, CColor3D inColor)
{
	m_fType = fRectangle;

	m_deltaRect = 6.00;
	m_Scale = 2.00;

	m_P1.x = x - m_deltaRect;
	m_P1.y = y - m_deltaRect;

	m_P3.x = x + m_deltaRect;
	m_P3.y = y + m_deltaRect;

	auto pairP2P4 = GetP2P4(m_P1, m_P3);

	m_P2 = pairP2P4.first;
	m_P4 = pairP2P4.second;

	m_Color = inColor;
}

CRect2D::CRect2D(int x, int y, const float inDelta)
{
	m_fType = fRectangle;

	m_deltaRect = 6.00;
	m_Scale = 2.00;
	
	m_P1.x = x - inDelta;
	m_P1.y = y - inDelta;

	m_P3.x = x + inDelta;
	m_P3.y = y + inDelta;

	auto pairP2P4 = GetP2P4(m_P1, m_P3);

	m_P2 = pairP2P4.first;
	m_P4 = pairP2P4.second;

	m_Color.SetRGB(255, 0, 0);
}

CRect2D::~CRect2D()
{
}

void CRect2D::ChangePoints(CPoint2D inP1, CPoint2D inP3)
{
	m_P1 = inP1;
	m_P3 = inP3;
}

void CRect2D::ChangePoints(float inDeltaX, float inDeltaY)
{

}

std::list<CPoint2D*> CRect2D::GetPoints()
{
	std::list<CPoint2D*> rtnList;
	rtnList.push_back(&m_P1);
	rtnList.push_back(&m_P2);
	rtnList.push_back(&m_P3);
	rtnList.push_back(&m_P4);

	return rtnList;
}

void CRect2D::SetDelta(const int inDeltaX, const int inDeltaY)
{

	m_P1.x += inDeltaX;
	m_P1.y += inDeltaY;

	m_P2.x += inDeltaX;
	m_P2.y += inDeltaY;

	m_P3.x += inDeltaX;
	m_P3.y += inDeltaY;

	m_P4.x += inDeltaX;
	m_P4.y += inDeltaY;
}

void CRect2D::SetNewCoord(const int inX, const int inY)
{
	double fSize = (m_P3.x - m_P1.x) / 2;
	
	m_P1.x = inX - fSize;
	m_P1.y = inY - fSize;

	m_P3.x = inX + fSize;
	m_P3.y = inY + fSize;

	auto pairP2P4 = GetP2P4(m_P1, m_P3);

	m_P2 = pairP2P4.first;
	m_P4 = pairP2P4.second;
}

bool CRect2D::SetNewScale(bool IsUp)
{
	
	if (IsUp)
	{
		m_P1.x -= m_Scale;
		m_P1.y -= m_Scale;

		m_P3.x += m_Scale;
		m_P3.y += m_Scale;
	}
	else 
	{
		m_P1.x += m_Scale;
		m_P1.y += m_Scale;

		m_P3.x -= m_Scale;		
		m_P3.y -= m_Scale;
	}

	auto pairP2P4 = GetP2P4(m_P1, m_P3);
	
	m_P2 = pairP2P4.first;
	m_P4 = pairP2P4.second;

	return true;
}

bool CRect2D::CheckInWindow(int InCondition, bool IsUp, CPoint2D InCenterXY, int InWinWidth, int InWinHeight)
{	
	switch (InCondition)
	{
		case 0:
		{
			if (IsUp) //NewScale //0
			{
				CPoint2D tmpP1(0, 0);
				CPoint2D tmpP3(0, 0);

				tmpP1.x = m_P1.x - m_Scale;
				tmpP1.y = m_P1.y + m_Scale;

				tmpP3.x = m_P3.x - m_Scale;
				tmpP3.y = m_P3.y + m_Scale;

				if ((tmpP1.x > 100) && (tmpP1.x < (InWinWidth - 2)) && (tmpP1.y > 0) && (tmpP1.y < (InWinHeight - 2))
					&& ((tmpP3.x < (InWinWidth - 2)) && (tmpP3.y < (InWinHeight - 2))))
				{
					SetNewScale(IsUp);
					return true;
				}
			}
			else
			{
				SetNewScale(IsUp);
				return true;
			}

			break;
		}

		case 1: //NewDelta
		{
			double fSize = (m_P3.x - m_P1.x) / 2;

			CPoint2D tmpP1(m_P1.x, m_P1.y);
			CPoint2D tmpP2(m_P2.x, m_P2.y);
			CPoint2D tmpP3(m_P3.x, m_P3.y);
			CPoint2D tmpP4(m_P4.x, m_P4.y);

			tmpP1.x += InCenterXY.x;
			tmpP1.y += InCenterXY.y;

			tmpP2.x += InCenterXY.x;
			tmpP2.y += InCenterXY.y;

			tmpP3.x += InCenterXY.x;
			tmpP3.y += InCenterXY.y;

			tmpP4.x += InCenterXY.x;
			tmpP4.y += InCenterXY.y;

			if ((tmpP1.x > 100) && (tmpP1.x < (InWinWidth - 2)) && (tmpP1.y > 0) && (tmpP1.y < (InWinHeight - 2))
				&& (tmpP3.x < InWinWidth - 2) && (tmpP3.x > 100) && (tmpP3.y >0) && (tmpP3.y < (InWinHeight - 2)))
			{
				SetDelta(InCenterXY.x, InCenterXY.y);

				return true;
			}

			break;
		}

		case 2: //NewCoords
		{

			double fSize = (m_P3.x - m_P1.x) / 2;

			CPoint2D tmpP1(0, 0);
			CPoint2D tmpP3(0, 0);

			tmpP1.x = InCenterXY.x - fSize;
			tmpP1.y = InCenterXY.y - fSize;

			tmpP3.x = InCenterXY.x + fSize;
			tmpP3.y = InCenterXY.y + fSize;

			if((tmpP1.x > 100) && (tmpP1.x < (InWinWidth - 2)) && (tmpP1.y > 0) && (tmpP1.y < (InWinHeight - 2))
				&& (tmpP3.x < InWinWidth - 2) && (tmpP3.x > 100) && (tmpP3.y > 0) && (tmpP3.y < (InWinHeight - 2)))
			{
				SetNewCoord(InCenterXY.x, InCenterXY.y);
			}

			break;
		}

		default:
			break;
	}
	
	return false;
}

std::pair<CPoint2D, CPoint2D> CRect2D::GetP2P4(CPoint2D inP1, CPoint2D inP3)
{
	std::pair<CPoint2D, CPoint2D> rtnPoints;

	rtnPoints.first.x = inP1.x;
	rtnPoints.first.y = inP3.y;

	rtnPoints.second.x = inP3.x;
	rtnPoints.second.y = inP1.y;

	return rtnPoints;
}
