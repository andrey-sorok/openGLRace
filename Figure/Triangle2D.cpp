

#include "Triangle2D.h"
#include "Color3D.h"

CTriangle2D::CTriangle2D()
{	
	m_Scale = 2.00;

	m_fType = fTriangle;

	m_IndOjects2D = -1;

	m_deltaTriangle = 2.00;

	m_P1(0.00,0.00);
	m_P2(0.00, 0.00);
	m_P3(0.00, 0.00);

	m_Color (0, 0, 0);
}


CTriangle2D::~CTriangle2D()
{
}

CTriangle2D::CTriangle2D(const int inCnterX, const int inCnterY)
{
	m_Scale = 2.00;

	m_fType = fTriangle;

	m_deltaTriangle = 10.00;

	m_P1.x = inCnterX;
	m_P1.y = inCnterY - m_deltaTriangle;

	m_P2.x = inCnterX - m_deltaTriangle;
	m_P2.y = inCnterY + m_deltaTriangle;
	
	m_P3.x = inCnterX + m_deltaTriangle;
	m_P3.y = inCnterY + m_deltaTriangle;
	
	m_Color.SetRGB(255, 0, 0);
}

CTriangle2D::CTriangle2D(const int inCnterX, const int inCnterY, CColor3D inColor)
{
	m_Scale = 2.00;

	m_fType = fTriangle;

	m_deltaTriangle = 10.00;

	m_P1.x = inCnterX;
	m_P1.y = inCnterY - m_deltaTriangle;

	m_P2.x = inCnterX - m_deltaTriangle;
	m_P2.y = inCnterY + m_deltaTriangle;

	m_P3.x = inCnterX + m_deltaTriangle;
	m_P3.y = inCnterY + m_deltaTriangle;

	m_Color = inColor;
}

void CTriangle2D::ChangePoints(CPoint2D inP1, CPoint2D inP2, CPoint2D inP3)
{
	m_P1 = inP1;
	m_P2 = inP2;
	m_P3 = inP3;
}

CTriangle2D::CTriangle2D(CPoint2D inP1, CPoint2D inP2, CPoint2D inP3, CColor3D inColor)
{
	m_fType = fTriangle;

	m_Color = inColor;

	m_P1 = inP1;
	m_P2 = inP2;
	m_P3 = inP3;
}

void CTriangle2D::SetDelta(const int inDeltaX, const int inDeltaY)
{
	m_P1.x += inDeltaX;
	m_P1.y += inDeltaY;

	m_P2.x += inDeltaX;
	m_P2.y += inDeltaY;

	m_P3.x += inDeltaX;
	m_P3.y += inDeltaY;
}

bool CTriangle2D::SetNewScale(bool IsUp)
{
	if (IsUp)
	{
		m_P1.y -= m_Scale;

		m_P2.x -= m_Scale;
		m_P2.y += m_Scale;

		m_P3.x += m_Scale;
		m_P3.y += m_Scale;
	}
	else
	{
		m_P1.y += m_Scale;

		m_P2.x += m_Scale;
		m_P2.y -= m_Scale;

		m_P3.x -= m_Scale;
		m_P3.y -= m_Scale;
	}

	return true;
}

CPoint2D CTriangle2D::GetLineItersect(const CPoint2D line1P1, const CPoint2D line1P2,
	const CPoint2D line2P1, const CPoint2D line2P2)
{
	double a1, a2, b1, b2, c1, c2;
	double x, y, x1, y1, x2, y2, x3, y3, x4, y4;

	a1 = line1P1.y - line1P2.y;//y1 - y2;
	b1 = line1P2.x - line1P1.x;//x2 - x1;
	c1 = (line1P1.x*line1P2.y) - (line1P2.x*line1P1.y); //x1 * y2 - x2 * y1;
	a2 = line2P1.y - line2P2.y;//y3 - y4;
	b2 = line2P2.x - line2P1.x;//x4 - x3;
	c2 = (line2P1.x*line2P2.y) - (line2P2.x*line2P1.y);//x3 * y4 - x4 * y3;

	double det = a1 * b2 - a2 * b1;

	if (det > 0.01)
	{
		x = (b1 * c2 - b2 * c1) / det;
		y = (a2 * c1 - a1 * c2) / det;
	}
	else
	{
		return CPoint2D(0, 0);
	}
	return CPoint2D(x, y);
}

void CTriangle2D::SetNewCoord(const int inX, const int inY)
{
	// A m_P1
	// B m_P2
	// C m_P3

	CPoint2D a;
	a.x = ( m_P1.x + m_P2.x ) / 2;
	a.y = ( m_P1.y + m_P2.y ) / 2;

	CPoint2D b;
	b.x = ( m_P1.x + m_P3.x ) / 2;
	b.y = ( m_P1.y + m_P3.y ) / 2;

	CPoint2D p = GetLineItersect( a, m_P3, b, m_P2 );

	double moveX = inX - p.x ;
	double moveY = inY - p.y ;

	m_P1.x += moveX;
	m_P1.y += moveY;

	m_P2.x += moveX;
	m_P2.y += moveY;

	m_P3.x += moveX;
	m_P3.y += moveY;
}

std::list<CPoint2D*> CTriangle2D::GetPoints()
{
	std::list<CPoint2D*> rtnList;
	rtnList.push_back(&m_P1);
	rtnList.push_back(&m_P2);
	rtnList.push_back(&m_P3);

	return rtnList;
}

bool CTriangle2D::CheckInWindow(int InCondition, bool IsUp, CPoint2D InCenterXY, int InWinWidth, int InWinHeight)
{
	switch (InCondition)
	{
	case 0:
	{
		if (IsUp) //NewScale //0
		{
			CPoint2D tmpP1(m_P1.x, m_P1.y);
			CPoint2D tmpP2(m_P2.x, m_P2.y);
			CPoint2D tmpP3(m_P3.x, m_P3.y);

			tmpP1.y -= m_Scale;

			tmpP2.x -= m_Scale;
			tmpP2.y += m_Scale;

			tmpP3.x += m_Scale;
			tmpP3.y += m_Scale;

			if ((tmpP1.x > 100) && (tmpP1.x < (InWinWidth - 2)) && (tmpP1.y > 0) && (tmpP1.y < (InWinHeight - 2))
				&& ((tmpP2.x > 100) && (tmpP2.x < (InWinWidth - 2)) && (tmpP2.y > 0) && (tmpP2.y < (InWinHeight - 2))
				&& ((tmpP3.x > 100) && (tmpP3.x < (InWinWidth - 2)) && (tmpP3.y > 0) && (tmpP3.y < (InWinHeight - 2)))))
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
		CPoint2D tmpP1(m_P1.x, m_P1.y);
		CPoint2D tmpP2(m_P2.x, m_P2.y);
		CPoint2D tmpP3(m_P3.x, m_P3.y);

		tmpP1.x += InCenterXY.x;
		tmpP1.y += InCenterXY.y;

		tmpP2.x += InCenterXY.x;
		tmpP2.y += InCenterXY.y;

		tmpP3.x += InCenterXY.x;
		tmpP3.y += InCenterXY.y;

		if ((tmpP1.x > 100) && (tmpP1.x < (InWinWidth - 2)) && (tmpP1.y > 0) && (tmpP1.y < (InWinHeight - 2))
			&& ((tmpP2.x > 100) && (tmpP2.x < (InWinWidth - 2)) && (tmpP2.y > 0) && (tmpP2.y < (InWinHeight - 2))
				&& ((tmpP3.x > 100) && (tmpP3.x < (InWinWidth - 2)) && (tmpP3.y > 0) && (tmpP3.y < (InWinHeight - 2)))))
		{
			SetDelta(InCenterXY.x, InCenterXY.y);

			return true;
		}

		break;
	}

	case 2: //NewCoords
	{
		CPoint2D tmpP1(m_P1.x, m_P1.y);
		CPoint2D tmpP2(m_P2.x, m_P2.y);
		CPoint2D tmpP3(m_P3.x, m_P3.y);

		CPoint2D a;
		a.x = (m_P1.x + m_P2.x) / 2;
		a.y = (m_P1.y + m_P2.y) / 2;

		CPoint2D b;
		b.x = (m_P1.x + m_P3.x) / 2;
		b.y = (m_P1.y + m_P3.y) / 2;

		CPoint2D p = GetLineItersect(a, m_P3, b, m_P2);

		double moveX = InCenterXY.x - p.x;
		double moveY = InCenterXY.y - p.y;

		tmpP1.x += moveX;
		tmpP1.y += moveY;

		tmpP2.x += moveX;
		tmpP2.y += moveY;

		tmpP3.x += moveX;
		tmpP3.y += moveY;

		if ((tmpP1.x > 100) && (tmpP1.x < (InWinWidth - 2)) && (tmpP1.y > 0) && (tmpP1.y < (InWinHeight - 2))
			&& ((tmpP2.x > 100) && (tmpP2.x < (InWinWidth - 2)) && (tmpP2.y > 0) && (tmpP2.y < (InWinHeight - 2))
				&& ((tmpP3.x > 100) && (tmpP3.x < (InWinWidth - 2)) && (tmpP3.y > 0) && (tmpP3.y < (InWinHeight - 2)))))
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
