#ifndef __TRIANGLE2D_
#define __TRIANGLE2D_

#include "Point2D.h"
#include "FigureBase.h"

#include <list>

class CPoint2D;

class CTriangle2D : public CFigureBase
{
private:
	CPoint2D m_P1;
	CPoint2D m_P2;
	CPoint2D m_P3;

	double m_deltaTriangle;

	double m_Scale;

	CPoint2D GetLineItersect(const CPoint2D line1P1, const CPoint2D line1P2, 
		const CPoint2D line2P1, const CPoint2D line2P2);
public:
	CTriangle2D();
	~CTriangle2D();

	CTriangle2D(const int inCnterX, const int inCnterY);
	CTriangle2D(const int inCnterX, const int inCnterY, CColor3D inColor);
	CTriangle2D(CPoint2D inP1, CPoint2D inP2, CPoint2D inP3, CColor3D inColor);


	void ChangePoints(CPoint2D inP1, CPoint2D inP2, CPoint2D inP3);
	
	void SetDelta(const int inDeltaX, const int inDeltaY);

	bool SetNewScale(bool IsUp);
	void SetNewCoord(const int inX, const int inY);

	std::list<CPoint2D*> GetPoints();

	/*InCondition	- 0 SetNewScale
	- 1 SetNewDelta
	- 2 SetNewCoord
	*/
	bool CheckInWindow(int InCondition, bool IsUp, CPoint2D InCenterXY, int InWinWidth, int InWinHeight);

};

#endif //__TRIANGLE2D_
