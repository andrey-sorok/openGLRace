#ifndef __RECT2D_
#define __RECT2D_

#include "FigureBase.h"
#include "Point2D.h"

#include <utility>
#include <list>

class CRect2D : public CFigureBase
{
private:
	CPoint2D m_P1;
	CPoint2D m_P3;

	CPoint2D m_P2;
	CPoint2D m_P4;

	double m_deltaRect;
	double m_Scale;

protected:
	std::pair<CPoint2D, CPoint2D> GetP2P4(CPoint2D inP1, CPoint2D inP3);

public:

	CRect2D();
	CRect2D(CPoint2D inP1, CPoint2D inP3, CColor3D inColor);
	
	CRect2D(int x, int y, CColor3D inColor);
	//__
	CRect2D(int x, int y, const float inDelta);
	//__
	~CRect2D();

	void ChangePoints(CPoint2D inP1, CPoint2D inP3);
	void ChangePoints(float inDeltaX, float inDeltaY);

	std::list<CPoint2D*> GetPoints();

	double GetScale() { return m_Scale; };

	void SetDelta(const int inDeltaX, const int inDeltaY);
	void SetNewCoord(const int inX, const int inY);
	bool SetNewScale(bool IsUp);

	/*InCondition	- 0 SetNewScale
					- 1 SetNewDelta
					- 2 SetNewCoord
	*/
	bool CheckInWindow(int InCondition, bool IsUp, CPoint2D InCenterXY, int InWinWidth, int InWinHeight);
};

#endif //__RECT2D_



