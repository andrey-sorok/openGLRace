#include "Line2D.h"



CLine2D::CLine2D()
{
	m_IndOjects2D = -1;

	m_P1(0.00, 0.00);
	m_P2(0.00, 0.00);

	m_Color(0, 0, 0);
}


CLine2D::~CLine2D()
{
}

CLine2D::CLine2D(CPoint2D inP1, CPoint2D inP2, CColor3D inColor)
{
	m_fType = fLine;
	//m_IndOjects2D = -1;

	m_P1 = inP1;
	m_P2 = inP2;

	m_Color = inColor;
}

void CLine2D::SetPoints(CPoint2D inP1, CPoint2D inP2)
{
	m_P1 = inP1;
	m_P2 = inP2;
}

void CLine2D::ChangeColor(CColor3D inColor)
{
	m_Color = inColor;
}

std::list<CPoint2D*> CLine2D::GetPoints()
{
	std::list<CPoint2D*> rtnList;
	rtnList.push_back(&m_P1);
	rtnList.push_back(&m_P2);

	return rtnList;
}
