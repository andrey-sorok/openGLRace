#include "FigureBase.h"

CFigureBase::CFigureBase()
{
	m_Color(0, 0, 0);
	m_IndOjects2D = -1;
}


CFigureBase::~CFigureBase()
{
}

void CFigureBase::SetColor(CColor3D inColor)
{
	m_Color = inColor;
}

CColor3D * CFigureBase::GetColor()
{
	return &m_Color;
}

void CFigureBase::SetIndObject2D(int Ind)
{
	m_IndOjects2D = Ind;
}

int CFigureBase::GetIndObject2D()
{
	return m_IndOjects2D;
}
