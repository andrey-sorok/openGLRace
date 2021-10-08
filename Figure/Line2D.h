#ifndef __LINE2D_
#define __LINE2D_

#include "FigureBase.h"
#include "Point2D.h"

#include <list>

class CLine2D :	public CFigureBase
{
private:
	CPoint2D m_P1;
	CPoint2D m_P2;

	//int m_IndOjects2D;
public:
	CLine2D();
	~CLine2D();

	CLine2D(CPoint2D inP1, CPoint2D inP2, CColor3D inColor);

	void SetPoints(CPoint2D inP1, CPoint2D inP2);
	//void ChangePoints(float inDeltaX, float inDeltaY);
	void ChangeColor(CColor3D inColor);

	std::list<CPoint2D*> GetPoints();
};

#endif //__LINE2D_

