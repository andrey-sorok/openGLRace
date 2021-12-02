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
