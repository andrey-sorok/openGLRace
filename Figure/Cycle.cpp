#include "Cycle.h"

#define _USE_MATH_DEFINES

#include <math.h>

CCycle::CCycle()
{
}


CCycle::~CCycle()
{
}

CCycle::CCycle(const CPoint2D inCenter, const double inRadius, CColor3D inColor)
{
	m_fType = fCycle;

	m_Center = inCenter;
	m_Radius = inRadius;

	m_Color = inColor;

	m_NumSegments = 50;

	m_Scale = 2.00;
}

CCycle::CCycle(const CPoint2D inCenter, CColor3D inColor)
{
	m_fType = fCycle;

	m_Center = inCenter;
	m_Radius = 10.00;

	m_Color = inColor;

	m_NumSegments = 50;

	m_Scale = 2.00;
}

CCycle::CCycle(const CPoint2D inCenter)
{
	m_fType = fCycle;

	m_Center = inCenter;
	m_Radius = 10.00;

	m_Color = CColor3D(255, 0, 0);

	m_NumSegments = 50;

	m_Scale = 2.00;
}

void CCycle::SetNewCoord(const int inX, const int inY)
{
	double moveX = inX - m_Center.x;
	double moveY = inY - m_Center.y;

	m_Center.x += moveX;
	m_Center.y += moveY;
}

bool CCycle::SetNewScale(bool IsUp)
{
	if (IsUp)
	{
		m_Radius += m_Scale;
	}
	else
	{
		m_Radius -= m_Scale;
	}

	return true;
}

bool CCycle::CheckInWindow(int InCondition, bool IsUp, CPoint2D InCenterXY, int InWinWidth, int InWinHeight)
{
	switch (InCondition)
	{
	case 0:
	{
		if (IsUp) //NewScale //0
		{
			double tmpRadius = m_Radius + m_Scale;

			if (((m_Center.x - tmpRadius) > 100) && ((m_Center.x + tmpRadius) < (InWinWidth - 2))
				&& ((m_Center.y - tmpRadius) > 0) && ((m_Center.y + tmpRadius) < (InWinHeight - 2)))
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

		CPoint2D tmpCenter(m_Center.x + InCenterXY.x, m_Center.y + InCenterXY.y);

		bool IsXCorrect = ((tmpCenter.x - (m_Radius)) > 100) && ((tmpCenter.x + (m_Radius)) < (InWinWidth - 2));
		bool IsYCorrect = ((tmpCenter.y - (m_Radius)) > 0) && ((tmpCenter.y + (m_Radius)) < (InWinHeight - 2));

		if ((IsXCorrect) && (IsYCorrect))
		{
			SetDelta(InCenterXY.x, InCenterXY.y);

			return true;
		}
		break;
	}

	case 2: //NewCoords
	{

		double moveX = InCenterXY.x - m_Center.x;
		double moveY = InCenterXY.y - m_Center.y;

		CPoint2D tmpCenter(m_Center.x, m_Center.y);

		tmpCenter.x += moveX;
		tmpCenter.y += moveY;
	
		bool IsXCorrect = ((tmpCenter.x - (m_Radius)) > 100) && ((tmpCenter.x + (m_Radius)) < (InWinWidth - 2));
		bool IsYCorrect = ((tmpCenter.y - (m_Radius)) > 0) && ((tmpCenter.y + (m_Radius)) < (InWinHeight - 2));

		if ((IsXCorrect) && (IsYCorrect))
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

void CCycle::SetDelta(const int inDeltaX, const int inDeltaY)
{
	m_Center.x += inDeltaX;
	m_Center.y += inDeltaY;
}
