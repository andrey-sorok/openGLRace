#include "Condition.h"

#include "C2DModel.h"

CCondition::CCondition()
{
	m_WINWIDTH = 0;
	m_WINHEIGHT = 0;

	m_IsMouseMove = false;
	m_CurGameState = StartMenu;

	m_CurTrackState = fNoneTrack;

	m_CurFigure = fNone;
	CColor3D InitColor(0, 255, 0);
	m_CurColor = InitColor;

	m_MouseState = 0;
	m_MouseButton = 0;

	m_CarsFolder = "";

	m_NumCars = 0;

	m_NumCurbs = 5;//число смен цвета в бардюре 

	m_СurbOffset = 20.00;

	m_CerbHeight = 25;

	m_RectForCarInTrack.lengthX = 100;
	m_RectForCarInTrack.lengthY = 100;

	m_CurGameTime = 60000;
	m_NumTrackIntervals = 3;
	m_IntervalLength = m_CurGameTime / m_NumTrackIntervals;
	m_MaxTrackObj = 5;

	m_Left = 0.00;
	m_Right = 0.00;
	m_Up = 0.00;
	m_Down = 0.00;

	m_IsGenerate = false;

	m_Offset = 20.00;
}


CCondition::~CCondition()
{
}

void CCondition::SetWINWIDTH(int InWinWidth)
{
	m_WINWIDTH = InWinWidth;
}

void CCondition::SetWINHEIGHT(int InWinHeight)
{
	m_WINHEIGHT = InWinHeight;
}

void CCondition::SetLeftRightUpBottom(double left, double right, double up, double down)
{
	m_Left = left;
	m_Right = right;
	m_Up = up;
	m_Down = down;
}

std::list<double> CCondition::GetLeftRightUpBottom()
{
	std::list<double> rtnLst;
	rtnLst.push_back(m_Left);
	rtnLst.push_back(m_Right);
	rtnLst.push_back(m_Up);
	rtnLst.push_back(m_Down);
	return rtnLst;
}
